// Sakurasaki All Rights Reserved.


#include "Items/WeaverChestBase.h"

#include "Characters/WeaverBaseCharacter.h"
#include "Components/BoxComponent.h"
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

	ChestMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ChestMesh"));
	ChestMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ChestMesh->SetCollisionObjectType(ECC_WorldStatic);
	ChestMesh->SetupAttachment(GetRootComponent());
}

void AWeaverChestBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaverChestBase::HighlightActor_Implementation()
{
	IPawnInteractionInterface::HighlightActor_Implementation();
}

void AWeaverChestBase::UnHighlightActor_Implementation()
{
	IPawnInteractionInterface::UnHighlightActor_Implementation();
}

void AWeaverChestBase::Interact_Implementation(APawn* InstigatorPawn)
{
	IPawnInteractionInterface::Interact_Implementation(InstigatorPawn);
}

void AWeaverChestBase::Open_Implementation()
{
	if (OpenAnimation && ChestMesh)
	{
		ChestMesh->PlayAnimation(OpenAnimation, false);
	}
}
