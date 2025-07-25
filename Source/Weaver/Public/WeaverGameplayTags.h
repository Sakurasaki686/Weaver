// Sakurasaki All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace WeaverGameplayTags
{
	/** Input Tags **/
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Unequip_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ToggleGait);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Dodge);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Roll);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_BasicAttack_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_PowerAttack_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ToggleTuner);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ToggleElement);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ToggleEffect);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_BasicAegis);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Build);
	
	/** Player Tags **/
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Jump);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Dodge);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Roll);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_BasicAttack_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_PowerAttack_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_ToggleAffix_Tuner);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_ToggleAffix_Element);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_ToggleAffix_Effect);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HyperArmor);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Sculpt);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Rod);

	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Rod);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ActivateHyperArmor);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ApplyHyperArmorGE);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Invincible);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_InAir);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_InputMustBeHeld);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_InputBlocked);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_InputBlocked_Movement);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_InputBlocked_Jump);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_HyperArmor);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_HyperArmor_Activating);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_ToggleEquipping);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SculptMode_Build);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SculptMode_Dig);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_Dodge);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_Roll);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_HyperArmor);

	/** Enemy Tags **/
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_BasicAttack);


	/** Shared Tags **/
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);

	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_ProjectileHitTarget);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_InterruptCurrentMontage);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SpawnProjectile);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Immunity_HitReact);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Tuner_Focus);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Tuner_Diverge);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Tuner_Aegis);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Element_None);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Element_Fire);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Element_Frost);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Element_Lightning);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Element_Poison);
	
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Effect_None);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Effect_Split);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Effect_MultiShot);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Effect_Homing);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Effect_Pierce);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Effect_Ricochet);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Effect_Lifesteal);
	WEAVER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Projectile_Affix_Effect_DelayedDetonation);
}
