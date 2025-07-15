// Sakurasaki All Rights Reserved.


#include "WeaverGameplayTags.h"

namespace WeaverGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip_Rod, "InputTag.Equip.Rod");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip_Rod, "InputTag.Unequip.Rod");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ToggleGait, "InputTag.ToggleGait");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dodge, "InputTag.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "InputTag.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_BasicAttack_Rod, "InputTag.BasicAttack.Rod");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_PowerAttack_Rod, "InputTag.PowerAttack.Rod");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ToggleTuner, "InputTag.ToggleTuner");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ToggleElement, "InputTag.ToggleElement");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ToggleEffect, "InputTag.ToggleEffect");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_BasicAegis, "InputTag.MustBeHeld.BasicAegis");

	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Rod, "Player.Ability.Equip.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Rod, "Player.Ability.Unequip.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump, "Player.Ability.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dodge, "Player.Ability.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll, "Player.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_BasicAttack_Rod, "Player.Ability.Attack.BasicAttack.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_PowerAttack_Rod, "Player.Ability.Attack.PowerAttack.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ToggleAffix_Tuner, "Player.Ability.ToggleAffix.Tuner");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ToggleAffix_Element, "Player.Ability.ToggleAffix.Element");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ToggleAffix_Effect, "Player.Ability.ToggleAffix.Effect");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HyperArmor, "Player.Ability.HyperArmor");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Rod, "Player.Weapon.Rod");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Rod, "Player.Event.Equip.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Rod, "Player.Event.Unequip.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_ActivateHyperArmor, "Player.Event.ActivateHyperArmor");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_ApplyHyperArmorGE, "Player.Event.ApplyHyperArmorGE");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Invincible, "Player.State.Invincible");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_InAir, "Player.State.InAir");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_InputMustBeHeld, "Player.State.InputMustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_InputBlocked, "Player.State.InputBlocked");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_InputBlocked_Movement, "Player.State.InputBlocked.Movement");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_InputBlocked_Jump, "Player.State.InputBlocked.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_HyperArmor, "Player.State.HyperArmor");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_Dodge, "Player.Cooldown.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_Roll, "Player.Cooldown.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_HyperArmor, "Player.Cooldown.HyperArmor");

	/** Enemy Tags **/


	/** Shared Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_InterruptCurrentMontage, "Shared.Event.InterruptCurrentMontage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Tuner_Focus, "Shared.Projectile.Affix.Tuner.Focus");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Tuner_Diverge, "Shared.Projectile.Affix.Tuner.Diverge");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Tuner_Aegis, "Shared.Projectile.Affix.Tuner.Aegis");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Element_None, "Shared.Projectile.Affix.Element.None");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Element_Fire, "Shared.Projectile.Affix.Element.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Element_Frost, "Shared.Projectile.Affix.Element.Frost");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Element_Lightning, "Shared.Projectile.Affix.Element.Lightning");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Element_Poison, "Shared.Projectile.Affix.Element.Poison");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Effect_None, "Shared.Projectile.Affix.Effect.None");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Effect_Split, "Shared.Projectile.Affix.Effect.Split");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Effect_Homing, "Shared.Projectile.Affix.Effect.Homing");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Effect_Pierce, "Shared.Projectile.Affix.Effect.Pierce");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Effect_Ricochet, "Shared.Projectile.Affix.Effect.Ricochet");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Effect_Lifesteal, "Shared.Projectile.Affix.Effect.Lifesteal");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Projectile_Affix_Effect_DelayedDetonation, "Shared.Projectile.Affix.Effect.DelayedDetonation");
}
