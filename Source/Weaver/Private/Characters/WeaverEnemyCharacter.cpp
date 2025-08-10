// Sakurasaki All Rights Reserved.


#include "Characters/WeaverEnemyCharacter.h"

#include "WeaverFunctionLibrary.h"
#include "AbilitySystem/WeaverAttributeSet.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/WeaverWidgetBase.h"

AWeaverEnemyCharacter::AWeaverEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_PlayerSpellProjectile, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_EnemySpellProjectile, ECR_Ignore);

	GetMesh()->SetCollisionResponseToChannel(ECC_PlayerSpellProjectile, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_EnemySpellProjectile, ECR_Ignore);

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
	
	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandCollisionBox"));
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
	
	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandCollisionBox"));
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
	
	ThreatDetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ThreatDetectionBox"));
	ThreatDetectionBox->SetupAttachment(GetRootComponent());
	ThreatDetectionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	ThreatDetectionBox->SetCollisionResponseToChannel(ECC_PlayerSpellProjectile, ECR_Overlap);
	ThreatDetectionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ThreatDetectionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::AWeaverEnemyCharacter::OnThreatDetectionCollisionBoxBeginOverlap);
}

void AWeaverEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWeaverWidgetBase* HealthWidget = Cast<UWeaverWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AWeaverEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AWeaverEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	int32 AbilityApplyLevel = 1;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, AbilityApplyLevel]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(WeaverAbilitySystemComponent, AbilityApplyLevel);
				}
			}
		)
	);
}

UPawnCombatComponent* AWeaverEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AWeaverEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AWeaverEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

#if WITH_EDITOR
void AWeaverEnemyCharacter::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}
#endif

void AWeaverEnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UWeaverFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			EnemyCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void AWeaverEnemyCharacter::OnThreatDetectionCollisionBoxBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeaverEnemyCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	Super::OnHealthChanged(Data);
	
	const float NewHealth = Data.NewValue;
	const float MaxHealth = WeaverAttributeSet->GetMaxHealth();

	if (!bHasTriggeredHalfHealthEvent && NewHealth <= MaxHealth / 2.f)
	{
		bHasTriggeredHalfHealthEvent = true;

		OnHealthHalfThreshold();
	}
}

void AWeaverEnemyCharacter::OnHealthHalfThreshold_Implementation()
{
}
