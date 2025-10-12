#include "pch.h"
#include "Abilities.h"
#include "Utils.h"
#include "Inventory.h"
#include "Player.h"

void Abilities::ServerActivateAbility(UObject* Context, FFrame& Stack)
{
	FGameplayAbilitySpecHandle Handle;
	bool bInputPressed = false;
	FPredictionKey PredictionKey;

	Stack.StepCompiledIn(&Handle);
	Stack.StepCompiledIn(&bInputPressed);
	Stack.StepCompiledIn(&PredictionKey);
	Stack.IncrementCode();

	auto Controller = (AFortPlayerControllerAthena*)Context;
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	auto Spec = AbilitySystem->FindAbilitySpecFromHandle(Handle);
	if (!Spec) return;
	if (!Spec->Ability) return;

	AbilitySystem->TryActivateAbility(Handle, true);
}

void Abilities::ServerEndAbility(UObject* Context, FFrame& Stack)
{
	FGameplayAbilitySpecHandle Handle;
	FPredictionKey PredictionKey;
	FGameplayAbilityActivationInfo ActivationInfo;

	Stack.StepCompiledIn(&Handle);
	Stack.StepCompiledIn(&PredictionKey);
	Stack.StepCompiledIn(&ActivationInfo);
	Stack.IncrementCode();

	auto Controller = (AFortPlayerControllerAthena*)Context;
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	auto Spec = AbilitySystem->FindAbilitySpecFromHandle(Handle);
	if (!Spec || !Spec->Ability) return;

	Spec->Ability->EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void Abilities::ServerTryActivateAbility(UObject* Context, FFrame& Stack)
{
	FGameplayAbilitySpecHandle Handle;
	bool bInputPressed = false;
	FPredictionKey PredictionKey;

	Stack.StepCompiledIn(&Handle);
	Stack.StepCompiledIn(&bInputPressed);
	Stack.StepCompiledIn(&PredictionKey);
	Stack.IncrementCode();

	auto Controller = (AFortPlayerControllerAthena*)Context;
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	auto Spec = AbilitySystem->FindAbilitySpecFromHandle(Handle);
	if (!Spec || !Spec->Ability) return;

	AbilitySystem->TryActivateAbility(Handle, true);
}

void Abilities::ServerActivateAbilityWithTargetData(UObject* Context, FFrame& Stack)
{
	FGameplayAbilitySpecHandle Handle;
	FGameplayAbilityTargetDataHandle TargetData;
	FPredictionKey PredictionKey;

	Stack.StepCompiledIn(&Handle);
	Stack.StepCompiledIn(&TargetData);
	Stack.StepCompiledIn(&PredictionKey);
	Stack.IncrementCode();

	auto Controller = (AFortPlayerControllerAthena*)Context;
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	auto Spec = AbilitySystem->FindAbilitySpecFromHandle(Handle);
	if (!Spec || !Spec->Ability) return;

	AbilitySystem->ServerTryActivateAbilityWithTargetData(Handle, TargetData, PredictionKey);
}

void Abilities::ServerCancelAbility(UObject* Context, FFrame& Stack)
{
	FGameplayAbilitySpecHandle Handle;
	FPredictionKey PredictionKey;

	Stack.StepCompiledIn(&Handle);
	Stack.StepCompiledIn(&PredictionKey);
	Stack.IncrementCode();

	auto Controller = (AFortPlayerControllerAthena*)Context;
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	auto Spec = AbilitySystem->FindAbilitySpecFromHandle(Handle);
	if (!Spec || !Spec->Ability) return;

	Spec->Ability->CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void Abilities::ServerConfirmTargetData(UObject* Context, FFrame& Stack)
{
	FGameplayAbilitySpecHandle Handle;
	FPredictionKey PredictionKey;
	FGameplayAbilityTargetDataHandle TargetData;

	Stack.StepCompiledIn(&Handle);
	Stack.StepCompiledIn(&PredictionKey);
	Stack.StepCompiledIn(&TargetData);
	Stack.IncrementCode();

	auto Controller = (AFortPlayerControllerAthena*)Context;
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	AbilitySystem->ServerConfirmTargetData(Handle, PredictionKey, TargetData);
}

void Abilities::ServerSendAbilityRPCBatch(UObject* Context, FFrame& Stack)
{
	FGameplayAbilitySpecHandle Handle;
	bool bInputPressed = false;
	FPredictionKey PredictionKey;

	Stack.StepCompiledIn(&Handle);
	Stack.StepCompiledIn(&bInputPressed);
	Stack.StepCompiledIn(&PredictionKey);
	Stack.IncrementCode();

	auto Controller = (AFortPlayerControllerAthena*)Context;
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	auto Spec = AbilitySystem->FindAbilitySpecFromHandle(Handle);
	if (!Spec || !Spec->Ability) return;

	AbilitySystem->ServerTryActivateAbility(Handle, true);
}

void Abilities::OnAbilityInputPressed(UObject* Context, FFrame& Stack)
{
	FGameplayAbilitySpecHandle Handle;
	Stack.StepCompiledIn(&Handle);
	Stack.IncrementCode();

	auto Controller = (AFortPlayerControllerAthena*)Context;
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	auto Spec = AbilitySystem->FindAbilitySpecFromHandle(Handle);
	if (!Spec) return;

	Spec->bInputPressed = true;
}

void Abilities::OnAbilityInputReleased(UObject* Context, FFrame& Stack)
{
	FGameplayAbilitySpecHandle Handle;
	Stack.StepCompiledIn(&Handle);
	Stack.IncrementCode();

	auto Controller = (AFortPlayerControllerAthena*)Context;
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	auto Spec = AbilitySystem->FindAbilitySpecFromHandle(Handle);
	if (!Spec) return;

	Spec->bInputPressed = false;
}

void Abilities::CancelAllAbilities(AFortPlayerControllerAthena* Controller)
{
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	for (auto& Spec : AbilitySystem->ActivatableAbilities.Items)
		if (Spec.Ability)
			Spec.Ability->CancelAbility(Spec.Handle, nullptr, {}, true);
}

void Abilities::GrantDefaultAbilities(AFortPlayerControllerAthena* Controller)
{
	if (!Controller) return;

	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	static auto SprintAbility = Utils::FindObject<UClass>(L"/Game/Abilities/Player/Generic/GA_DefaultPlayer_Sprint.GA_DefaultPlayer_Sprint_C");
	static auto JumpAbility = Utils::FindObject<UClass>(L"/Game/Abilities/Player/Generic/GA_DefaultPlayer_Jump.GA_DefaultPlayer_Jump_C");

	if (SprintAbility)
		AbilitySystem->GiveAbility(SprintAbility, 1, 0);

	if (JumpAbility)
		AbilitySystem->GiveAbility(JumpAbility, 1, 0);
}

void Abilities::RemoveAbility(AFortPlayerControllerAthena* Controller, UClass* AbilityClass)
{
	if (!Controller) return;
	auto AbilitySystem = Controller->GetAbilitySystemComponent();
	if (!AbilitySystem) return;

	for (auto& Spec : AbilitySystem->ActivatableAbilities.Items)
	{
		if (Spec.Ability == AbilityClass)
		{
			AbilitySystem->ClearAbility(Spec.Handle);
			break;
		}
	}
}

void Abilities::Hook()
{
	Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerActivateAbility", ServerActivateAbility);
	Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerEndAbility", ServerEndAbility);
	Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerTryActivateAbility", ServerTryActivateAbility);
	Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerActivateAbilityWithTargetData", ServerActivateAbilityWithTargetData);
	Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerCancelAbility", ServerCancelAbility);
	Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerConfirmTargetData", ServerConfirmTargetData);
	Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerSendAbilityRPCBatch", ServerSendAbilityRPCBatch);
}