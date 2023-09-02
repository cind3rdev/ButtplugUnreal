// Copyright 2023 @Cinder. Licensed MIT.

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
