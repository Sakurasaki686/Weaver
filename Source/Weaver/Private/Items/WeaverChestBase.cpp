// Sakurasaki All Rights Reserved.


#include "Items/WeaverChestBase.h"

#include "AbilitySystem/WeaverAttributeSet.h"
#include "Characters/WeaverBaseCharacter.h"
#include "Characters/WeaverPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/WeaverRewardComponent.h"
#include "Kismet/GameplayStatics.h"

AWeaverChestBase::AWeaverChestBase()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetWorldScale3D(FVector(0.7f, 0.7f, 0.7f));
	SetRootComponent(DefaultSceneRoot);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractionBox->SetCollisionResponseToChannel(ECC_PlayerSpellProjectile, ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_EnemySpellProjectile, ECR_Ignore);
	InteractionBox->SetupAttachment(GetRootComponent());
	
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AWeaverChestBase::OnInteractionBoxBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AWeaverChestBase::OnInteractionBoxEndOverlap);

	ChestMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ChestMesh"));
	ChestMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ChestMesh->SetCollisionObjectType(ECC_WorldStatic);
	ChestMesh->SetupAttachment(GetRootComponent());

	RewardComponent = CreateDefaultSubobject<UWeaverRewardComponent>(TEXT("RewardComponent"));
	
	RewardComponent->OnRewardSelectionStarted.AddDynamic(this, &ThisClass::StartRewardSelection);
}

void AWeaverChestBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaverChestBase::Interact_Implementation(AActor* InInstigator)
{
	IPawnInteractionInterface::Interact_Implementation(InInstigator);

	if (CanOpen(InInstigator))
	{
		Open(InInstigator);
	}
	else
	{
		if (!bHasOpened)
		{
			Execute_ShowInteractionWarningFeedback(InInstigator, ChestInteractionWarningHint);
		}
	}
}

bool AWeaverChestBase::CanOpen(AActor* InInstigator)
{
	if (bHasOpened)
	{
		return false;
	}
	
	if (AWeaverPlayerCharacter* Player = Cast<AWeaverPlayerCharacter>(InInstigator))
	{
		if (UWeaverAttributeSet* AttributeSet = Player->GetWeaverAttributeSet())
		{
			if (AttributeSet->GetAether() >= AetherCostToOpen)
			{
				return true;
			}
		}
	}
	
	return false;
}

void AWeaverChestBase::Open_Implementation(AActor* InInstigator)
{
}

void AWeaverChestBase::OnInteractionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->Implements<UPawnInteractionInterface>())
	{
		Execute_SetInteractionInfo(OtherActor, this, ChestInteractionHint);
	}
}

void AWeaverChestBase::OnInteractionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->Implements<UPawnInteractionInterface>())
	{
		Execute_SetInteractionInfo(OtherActor, nullptr, ChestInteractionHint);
	}
}

void AWeaverChestBase::StartRewardSelection_Implementation()
{
}

void AWeaverChestBase::FinishRewardSelection_Implementation()
{
}
