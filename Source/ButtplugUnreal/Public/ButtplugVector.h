// Copyright 2023 @Cinder. Licensed MIT.

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
