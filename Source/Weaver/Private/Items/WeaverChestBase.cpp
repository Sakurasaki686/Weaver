// Sakurasaki All Rights Reserved.


#include "Items/WeaverChestBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AWeaverChestBase::AWeaverChestBase()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SetRootComponent(InteractionBox);

	ChestMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ChestMesh"));
	ChestMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ChestMesh->SetCollisionObjectType(ECC_WorldStatic);
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
	if (OpenSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
	}

	if (OpenAnimation && ChestMesh)
	{
		ChestMesh->PlayAnimation(OpenAnimation, false);
	}
}
