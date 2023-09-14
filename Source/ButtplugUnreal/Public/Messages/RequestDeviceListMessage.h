// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "RequestDeviceListMessage.generated.h"

/**
 * RequestDeviceList Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/enumeration#requestdevicelist
 */
UCLASS()
class BUTTPLUGUNREAL_API URequestDeviceListMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	virtual FString GetMessageName() override;
};
