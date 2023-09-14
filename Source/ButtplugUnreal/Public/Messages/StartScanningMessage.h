// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "StartScanningMessage.generated.h"

/**
 * StartScanning Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/enumeration#startscanning
 */
UCLASS()
class BUTTPLUGUNREAL_API UStartScanningMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	virtual FString GetMessageName() override;
};
