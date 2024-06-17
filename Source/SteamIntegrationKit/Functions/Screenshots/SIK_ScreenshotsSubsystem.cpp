﻿// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_ScreenshotsSubsystem.h"

#include "Async/Async.h"


USIK_ScreenshotsSubsystem::USIK_ScreenshotsSubsystem()
{
#ifdef ONLINESUBSYSTEMSTEAM_PACKAGE
	m_CallbackScreenshotReady.Register(this, &USIK_ScreenshotsSubsystem::OnScreenshotReadyCallback);
	m_CallbackScreenshotRequested.Register(this, &USIK_ScreenshotsSubsystem::OnScreenshotRequestedCallback);
 	if(IsRunningDedicatedServer())
 	{
	m_CallbackScreenshotReady.SetGameserverFlag();
	m_CallbackScreenshotRequested.SetGameserverFlag();
}
#endif
}

USIK_ScreenshotsSubsystem::~USIK_ScreenshotsSubsystem()
{
#ifdef ONLINESUBSYSTEMSTEAM_PACKAGE
	m_CallbackScreenshotReady.Unregister();
	m_CallbackScreenshotRequested.Unregister();
#endif
}

void USIK_ScreenshotsSubsystem::OnScreenshotReadyCallback(ScreenshotReady_t* Callback)
{
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnScreenshotReady.Broadcast(Param.m_hLocal, static_cast<ESIK_Result>(Param.m_eResult));
	});
}

void USIK_ScreenshotsSubsystem::OnScreenshotRequestedCallback(ScreenshotRequested_t* Callback)
{
	auto Param = *Callback;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnScreenshotRequested.Broadcast();
	});
}