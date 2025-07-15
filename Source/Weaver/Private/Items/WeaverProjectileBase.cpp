// Sakurasaki All Rights Reserved.


#include "Items/WeaverProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "WeaverFunctionLibrary.h"
#include "WeaverGameplayTags.h"
#include "GameFramework/ProjectileMovementComponent.h"

AWeaverProjectileBase::AWeaverProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 700.f;
	ProjectileMovementComp->MaxSpeed = 900.f;
	ProjectileMovementComp->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;
}

void AWeaverProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::HandleHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::HandleOverlap);

	OnProjectileSpawn.Broadcast();

	// if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	// {
	// 	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	// }
}

void AWeaverProjectileBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnProjectileDestroy.Broadcast();
	
	Super::EndPlay(EndPlayReason);
}

void AWeaverProjectileBase::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
	
	APawn* HitPawn = Cast<APawn>(OtherActor);

	OnProjectileHit.Broadcast(OtherActor, Hit);

	if (bDestroyOnHit)
	{
		Destroy();
	}
}

void AWeaverProjectileBase::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// // Ensure we don't overlap with our instigator
	// if (OtherActor && OtherActor != GetInstigator())
	// {
	// 	OnProjectileOverlap.Broadcast(OtherActor);
	//
	// 	// This is where the Tuner logic for damage application happens
	// 	if (DamageTunerTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tuner.Focus"))))
	// 	{
	// 		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	// 		{
	// 			// Apply single target damage and then destroy
	// 			FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	// 			TargetASC->ApplyGameplayEffectToSelf(BaseDamageEffectClass.GetDefaultObject(), 1.0f, ContextHandle);
	// 			Destroy();
	// 		}
	// 	}
	// 	else if (DamageTunerTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Tuner.Diverge"))))
	// 	{
	// 		// Apply AoE damage and then destroy
	// 		TArray<AActor*> OverlappedActors;
	// 		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // Configure what to hit
	// 		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	//
	// 		UAbilitySystemBlueprintLibrary::AbilityTargetingSphereOverlap(this, GetActorLocation(), 300.f, ObjectTypes, nullptr, TArray<AActor*>(), OverlappedActors);
	//
	// 		for (AActor* TargetActor : OverlappedActors)
	// 		{
	// 			if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	// 			{
	// 				FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	// 				TargetASC->ApplyGameplayEffectToSelf(BaseDamageEffectClass.GetDefaultObject(), 1.0f, ContextHandle);
	// 			}
	// 		}
	// 		Destroy();
	// 	}
	// }
}

// void AWeaverProjectileBase::OnProjectileHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
// {
// 	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
// 	
// 	APawn* HitPawn = Cast<APawn>(OtherActor);
//
// 	// if (!HitPawn || !UWeaverFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
// 	// {
// 	// 	Destroy();
// 	// 	return;
// 	// }
//
// 	bool bIsValidBlock = false;
//
// 	// const bool bIsPlayerBlocking = UWeaverFunctionLibrary::NativeDoesActorHaveTag(HitPawn, WeaverGameplayTags::Player_Status_Blocking);
// 	//
// 	// if (bIsPlayerBlocking)
// 	// {
// 	// 	bIsValidBlock = UWeaverFunctionLibrary::IsValidBlock(this, HitPawn);
// 	// }
// 	//
// 	// FGameplayEventData Data;
// 	// Data.Instigator = this;
// 	// Data.Target = HitPawn;
// 	//
// 	// if (bIsValidBlock)
// 	// {
// 	// 	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
// 	// 		HitPawn,
// 	// 		WeaverGameplayTags::::Player_Event_SuccessfulBlock,
// 	// 		Data
// 	// 	);
// 	// }
// 	// else
// 	// {
// 	// 	HandleApplyProjectileDamage(HitPawn, Data);
// 	// }
//
// 	if (bDestroyOnHit)
// 	{
// 		Destroy();
// 	}
// }

// void AWeaverProjectileBase::OnProjectileBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	if (OverlappedActors.Contains(OtherActor))
// 	{
// 		return;
// 	}
//
// 	OverlappedActors.AddUnique(OtherActor);
//
// 	if (APawn* HitPawn = Cast<APawn>(OtherActor))
// 	{
// 		FGameplayEventData Data;
// 		Data.Instigator = GetInstigator();
// 		Data.Target = HitPawn;
//
// 		if (UWeaverFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
// 		{
// 			HandleApplyProjectileDamage(HitPawn, Data);
// 		}
// 	}
// }

void AWeaverProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload)
{
	// checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());
	// const bool bWasApplied = UWeaverFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);
	//
	// if (bWasApplied)
	// {
	// 	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
	// 		InHitPawn,
	// 		WeaverGameplayTags::Shared_Event_HitReact,
	// 		InPayload
	// 	);
	// }
}
