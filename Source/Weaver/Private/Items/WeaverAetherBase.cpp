// Sakurasaki All Rights Reserved.


#include "Items/WeaverAetherBase.h"

#include "NiagaraComponent.h"
#include "Characters/WeaverBaseCharacter.h"
#include "Characters/WeaverPlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

AWeaverAetherBase::AWeaverAetherBase()
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

void AWeaverAetherBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaverAetherBase::OnInteractionBoxBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeaverAetherBase::OnInteractionBoxEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
