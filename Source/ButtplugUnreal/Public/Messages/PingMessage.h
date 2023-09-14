// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "PingMessage.generated.h"

/**
 * Ping Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/status#ping
 */
UCLASS()
class BUTTPLUGUNREAL_API UPingMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	virtual FString GetMessageName() override;
};
