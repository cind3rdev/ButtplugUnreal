// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "ScanningFinishedMessage.generated.h"

/**
 * ScanningFinished Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/enumeration#scanningfinished
 */
UCLASS()
class BUTTPLUGUNREAL_API UScanningFinishedMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	virtual FString GetMessageName() override;
};
