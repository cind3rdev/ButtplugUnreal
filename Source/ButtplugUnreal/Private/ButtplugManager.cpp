// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#include "ButtplugManager.h"


void UButtplugManager::BeginPlay()
{
	Super::BeginPlay();

	OnConnected.AddDynamic(this, &UButtplugManager::HandleConnected);
}

void UButtplugManager::HandleConnected()
{
	if (ScanForDevicesOnConnected)
	{
		StartScanning();
	}
}

void UButtplugManager::VibrateForSeconds(int32 DeviceIndex, const float TimeInSeconds, const float Speed)
{
	BasicVibrate(DeviceIndex, Speed);
	
	FTimerHandle UnusedHandle;
	const auto StopDeviceDelegate = FTimerDelegate::CreateUObject(this, &UButtplugManager::StopDeviceCmd, DeviceIndex);
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, StopDeviceDelegate, TimeInSeconds, false);
}

void UButtplugManager::TestDevice(const int32 DeviceIndex)
{
	VibrateForSeconds(DeviceIndex, 1.0f, 0.25f);
}
