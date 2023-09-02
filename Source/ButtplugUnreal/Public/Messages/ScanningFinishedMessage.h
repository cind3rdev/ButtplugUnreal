// Copyright 2023 @Cinder. Licensed MIT.

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
