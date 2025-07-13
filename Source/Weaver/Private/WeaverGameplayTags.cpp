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
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_InputBlocked, "InputTag.InputBlocked");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_InputBlocked_Movement, "InputTag.InputBlocked.Movement");

	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Rod, "Player.Ability.Equip.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Rod, "Player.Ability.Unequip.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dodge, "Player.Ability.Dodge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll, "Player.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_BasicAttack_Rod, "Player.Ability.Attack.BasicAttack.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_PowerAttack_Rod, "Player.Ability.Attack.PowerAttack.Rod");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Rod, "Player.Weapon.Rod");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Rod, "Player.Event.Equip.Rod");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Rod, "Player.Event.Unequip.Rod");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Invincible, "Player.State.Invincible");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_InAir, "Player.State.InAir");

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
}
