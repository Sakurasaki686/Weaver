// Sakurasaki All Rights Reserved.


#include "Characters/WeaverPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaverGameplayTags.h"
#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "Components/Input/WeaverInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AWeaverPlayerCharacter::AWeaverPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));

	JumpMaxCount = 2;
	CurrentGait = CharacterDefaultGait;
}

void AWeaverPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaverPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(WeaverAbilitySystemComponent);
		}
	}
}

UPawnCombatComponent* AWeaverPlayerCharacter::GetPawnCombatComponent() const
{
	return PlayerCombatComponent;
}

void AWeaverPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	const ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UWeaverInputComponent* WeaverInputComponent = CastChecked<UWeaverInputComponent>(PlayerInputComponent);

	WeaverInputComponent->BindNativeInputAction(InputConfigDataAsset, WeaverGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	WeaverInputComponent->BindNativeInputAction(InputConfigDataAsset, WeaverGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	WeaverInputComponent->BindNativeInputAction(InputConfigDataAsset, WeaverGameplayTags::InputTag_ToggleGait, ETriggerEvent::Started, this, &ThisClass::Input_ToggleGait);

	// WeaverInputComponent->BindNativeInputAction(InputConfigDataAsset, WeaverGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	// WeaverInputComponent->BindNativeInputAction(InputConfigDataAsset, WeaverGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	// WeaverInputComponent->BindNativeInputAction(InputConfigDataAsset, WeaverGameplayTags::InputTag_PickUp_Stones, ETriggerEvent::Started, this, &ThisClass::Input_PickUpStonesStarted);
	
	WeaverInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void AWeaverPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	
	CachedMovementInput = FVector(MovementVector.Y, MovementVector.X, 0.0f);
	
	if (GetWeaverAbilitySystemComponent()->HasMatchingGameplayTag(WeaverGameplayTags::Player_State_InputBlocked_Movement))
	{
		return;
	}
	
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWeaverPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWeaverPlayerCharacter::Input_ToggleGait(const FInputActionValue& InputActionValue)
{
	switch (CurrentGait)
	{
	case EWeaverCharacterGait::Run:
		CurrentGait = EWeaverCharacterGait::Walk;
		GetCharacterMovement()->MaxWalkSpeed = MaxWalSpeed;
		break;
	case EWeaverCharacterGait::Walk:
		CurrentGait = EWeaverCharacterGait::Run;
		GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
		break;
	default:
		break;
	}
}

void AWeaverPlayerCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	WeaverAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AWeaverPlayerCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	WeaverAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

void AWeaverPlayerCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
}

void AWeaverPlayerCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
}

void AWeaverPlayerCharacter::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
}


