// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ButtplugDevice.generated.h"

/**
 * ButtplugDevice is an instance of a device connected to your Buttplug server.
 */
USTRUCT(Blueprintable)
struct BUTTPLUGUNREAL_API FButtplugDevice
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) FString DeviceName;
	UPROPERTY(BlueprintReadWrite) int32 DeviceIndex;
	UPROPERTY(BlueprintReadWrite) FString DeviceDisplayName;
};
