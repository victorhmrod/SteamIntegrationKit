﻿// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include <steam/steam_api.h>
#include <steam/isteamgameserver.h>
#include <steam/isteamgameserverstats.h>
#include <steam/steam_api_common.h>
#else
#include <steam_api_common.h>
#include <steam_gameserver.h>
#include <isteamgameserver.h>
#include <isteamgameserverstats.h>
#endif
THIRD_PARTY_INCLUDES_END
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_GameServerStatsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGSStatsReceivedDelegate, FSIK_SteamId, SteamID, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGSStatsStoredDelegate, FSIK_SteamId, SteamID, TEnumAsByte<ESIK_Result>, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGSStatsUnloadedDelegate, FSIK_SteamId, SteamID);
UCLASS() 
class STEAMINTEGRATIONKIT_API USIK_GameServerStatsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_GameServerStatsSubsystem();
	~USIK_GameServerStatsSubsystem();
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server Stats")
	FGSStatsReceivedDelegate OnGSStatsReceived;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server Stats")
	FGSStatsStoredDelegate OnGSStatsStored;

	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Game Server Stats")
	FGSStatsUnloadedDelegate OnGSStatsUnloaded;
	
private:
	STEAM_CALLBACK_MANUAL(USIK_GameServerStatsSubsystem, OnGSStatsReceivedCallbck, GSStatsReceived_t, m_CallbackGSStatsReceived);
	STEAM_CALLBACK_MANUAL(USIK_GameServerStatsSubsystem, OnGSStatsStoredCallbck, GSStatsStored_t, m_CallbackGSStatsStored);
	STEAM_CALLBACK_MANUAL(USIK_GameServerStatsSubsystem, OnGSStatsUnloadedCallbck, GSStatsUnloaded_t, m_CallbackGSStatsUnloaded);
};
