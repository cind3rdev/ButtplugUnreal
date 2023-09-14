// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ButtplugRotation.generated.h"

/**
 * ButtplugRotation represents a Rotation value when sending a LinearCmd message to a device.
 */
USTRUCT(Blueprintable)
struct BUTTPLUGUNREAL_API FButtplugRotation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) int32 Index;
	UPROPERTY(BlueprintReadWrite) float Speed;
	UPROPERTY(BlueprintReadWrite) bool Clockwise;
};
