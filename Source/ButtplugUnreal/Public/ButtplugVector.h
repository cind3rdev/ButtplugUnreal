// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ButtplugVector.generated.h"

/**
 * ButtplugVector represents a Vector value when sending a LinearCmd message to a device.
 */
USTRUCT(Blueprintable)
struct BUTTPLUGUNREAL_API FButtplugVector
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) int32 Index;
	UPROPERTY(BlueprintReadWrite) int32 Duration;
	UPROPERTY(BlueprintReadWrite) float Position;
};
