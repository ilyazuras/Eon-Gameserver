#pragma once
#include "pch.h"

class Looting
{
public:
	static void SetupLDSForPackage(TArray<FFortItemEntry>& LootDrops, SDK::FName Package, int i, FName TierGroup, int WorldLevel);

	static TArray<FFortItemEntry> ChooseLootForContainer(FName TierGroup, int LootTier = -1, int WorldLevel = 1);

	static bool SpawnLootHook(ABuildingContainer* Container);
	static __int64 PostUpdate(ABuildingContainer* BuildingContainer, uint32 a2, __int64 a3);

	static void SpawnLoot(FName& TierGroup, FVector Loc);
	static void SpawnFloorLootForContainer(UBlueprintGeneratedClass* ContainerType);
	static bool ServerOnAttemptInteract(ABuildingContainer* BuildingContainer, AFortPlayerPawn*);

	static bool PickLootDrops(UObject* Object, FFrame& Stack, bool* Ret);
	static AFortPickup* SpawnPickup(UObject* Object, FFrame& Stack, AFortPickup** Ret);
	static AFortPickup* K2_SpawnPickupInWorld(UObject* Object, FFrame& Stack, AFortPickup** Ret);
	static AFortPickup* SpawnItemVariantPickupInWorld(UObject* Object, FFrame& Stack, AFortPickup** Ret);

	static void SpawnConsumableActor(ABGAConsumableSpawner* Spawner);

	static inline __int64(*PostUpdateOG)(ABuildingContainer*, uint32, __int64);
	static void Hook();
};