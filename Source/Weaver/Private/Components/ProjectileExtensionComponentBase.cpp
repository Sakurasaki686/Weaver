// Sakurasaki All Rights Reserved.


#include "Components/ProjectileExtensionComponentBase.h"

#include "Items/WeaverProjectileBase.h"

UProjectileExtensionComponentBase::UProjectileExtensionComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UProjectileExtensionComponentBase::BeginPlay()
{
	Super::BeginPlay();

	OwningProjectile = Cast<AWeaverProjectileBase>(GetOwner());
	
	if (OwningProjectile)
	{
		OwningProjectile->OnProjectileOverlap.AddDynamic(this, &ThisClass::OnOwnerProjectileOverlap);
		OwningProjectile->OnProjectileHit.AddDynamic(this, &ThisClass::OnOwnerProjectileHit);
		OwningProjectile->OnProjectileDestroy.AddDynamic(this, &ThisClass::OnOwnerProjectileDestroy);
	}
}

void UProjectileExtensionComponentBase::InitializeComponentForProjectile_Implementation()
{
}

void UProjectileExtensionComponentBase::OnOwnerProjectileOverlap_Implementation(AActor* OverlappedActor)
{
}

void UProjectileExtensionComponentBase::OnOwnerProjectileHit_Implementation(AActor* HitActor, const FHitResult& HitResult)
{
}

void UProjectileExtensionComponentBase::OnOwnerProjectileDestroy_Implementation()
{
}
