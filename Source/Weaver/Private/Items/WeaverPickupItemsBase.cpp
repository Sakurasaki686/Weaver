// Sakurasaki All Rights Reserved.


#include "Items/WeaverPickupItemsBase.h"

#include "NiagaraComponent.h"
#include "Characters/WeaverBaseCharacter.h"
#include "Components/BoxComponent.h"

AWeaverPickupItemsBase::AWeaverPickupItemsBase()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractionBox->SetCollisionResponseToChannel(ECC_PlayerSpellProjectile, ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_EnemySpellProjectile, ECR_Ignore);
	InteractionBox->SetupAttachment(GetRootComponent());

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractionBoxBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractionBoxEndOverlap);

	AetherNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("AetherNiagaraComponent"));
	AetherNiagaraComponent->SetupAttachment(GetRootComponent());

	InitialLifeSpan = 10.f;
}

void AWeaverPickupItemsBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaverPickupItemsBase::OnInteractionBoxBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeaverPickupItemsBase::OnInteractionBoxEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
