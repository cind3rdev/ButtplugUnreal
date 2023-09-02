// Copyright 2023 @Cinder. Licensed MIT.

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
