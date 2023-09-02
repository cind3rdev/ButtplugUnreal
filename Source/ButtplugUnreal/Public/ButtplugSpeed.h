// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ButtplugSpeed.generated.h"

/**
 * ButtplugSpeed represents a Speed value when sending a VibrateCmd message to a device.
 */
USTRUCT(Blueprintable)
struct BUTTPLUGUNREAL_API FButtplugSpeed
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) int32 Index;
	UPROPERTY(BlueprintReadWrite) float Speed;
};
