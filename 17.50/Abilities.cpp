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

    if (!Spec->Ability)
        return;

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
    if (!Spec || !Spec->Ability)
        return;

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
    if (!Spec || !Spec->Ability)
        return;

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
    if (!Spec || !Spec->Ability)
        return;

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
    if (!Spec || !Spec->Ability)
        return;

    Spec->Ability->CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void Abilities::Hook()
{
    Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerActivateAbility", ServerActivateAbility);
    Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerEndAbility", ServerEndAbility);
    Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerTryActivateAbility", ServerTryActivateAbility);
    Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerActivateAbilityWithTargetData", ServerActivateAbilityWithTargetData);
    Utils::ExecHook(L"/Script/FortniteGame.FortAbilitySystemComponent.ServerCancelAbility", ServerCancelAbility);
}