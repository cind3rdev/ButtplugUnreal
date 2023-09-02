// Copyright 2023 @Cinder. Licensed MIT.

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
