// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ButtplugScalar.generated.h"

/**
 * ButtplugSpeed represents a Speed value when sending a ScalarCmd message to a device.
 */
USTRUCT(Blueprintable)
struct BUTTPLUGUNREAL_API FButtplugScalar
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) int32 Index;
	UPROPERTY(BlueprintReadWrite) float Scalar;
	UPROPERTY(BlueprintReadWrite) FString ActuatorType;
};
