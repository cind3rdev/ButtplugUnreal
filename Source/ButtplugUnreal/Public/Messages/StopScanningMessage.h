// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "StopScanningMessage.generated.h"

/**
 * StopScanning Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/enumeration#stopscanning
 */
UCLASS()
class BUTTPLUGUNREAL_API UStopScanningMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	virtual FString GetMessageName() override;
};
