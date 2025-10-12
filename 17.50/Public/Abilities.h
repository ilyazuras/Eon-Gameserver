#pragma once
#include "pch.h"

struct FGameplayAbilitySpecHandle
{
	int Handle;
};

struct FGameplayAbilityActivationInfo
{
	int ActivationMode;
	FPredictionKey PredictionKeyWhenActivated;
};

struct FGameplayAbilitySpec
{
	FGameplayAbilitySpecHandle Handle;
	UClass* Ability;
	int Level;
	bool bInputPressed;
	bool bActive;
};

struct FGameplayAbilityTargetDataHandle
{
	TArray<void*> Data;
};

class Abilities
{
public:
	static void ServerActivateAbility(UObject* Context, FFrame& Stack);
	static void ServerEndAbility(UObject* Context, FFrame& Stack);
	static void ServerTryActivateAbility(UObject* Context, FFrame& Stack);
	static void ServerActivateAbilityWithTargetData(UObject* Context, FFrame& Stack);
	static void ServerCancelAbility(UObject* Context, FFrame& Stack);
	static void ServerConfirmTargetData(UObject* Context, FFrame& Stack);
	static void ServerSendAbilityRPCBatch(UObject* Context, FFrame& Stack);
	static void OnAbilityInputPressed(UObject* Context, FFrame& Stack);
	static void OnAbilityInputReleased(UObject* Context, FFrame& Stack);
	static void CancelAllAbilities(AFortPlayerControllerAthena* Controller);
	static void GrantDefaultAbilities(AFortPlayerControllerAthena* Controller);
	static void RemoveAbility(AFortPlayerControllerAthena* Controller, UClass* AbilityClass);
	static void Hook();
};