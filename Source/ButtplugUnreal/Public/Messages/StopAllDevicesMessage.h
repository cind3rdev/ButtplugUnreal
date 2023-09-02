// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "StopAllDevicesMessage.generated.h"

/**
 * StopAllDevices Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/generic#stopalldevices
 */
UCLASS()
class BUTTPLUGUNREAL_API UStopAllDevicesMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	virtual FString GetMessageName() override;
};
