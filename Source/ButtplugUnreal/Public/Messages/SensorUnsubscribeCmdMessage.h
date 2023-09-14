// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "SensorUnsubscribeCmdMessage.generated.h"

/**
 * SensorUnsubscribeCmd Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/sensors/#sensorunsubscribecmd
 */
UCLASS()
class BUTTPLUGUNREAL_API USensorUnsubscribeCmdMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) int32 DeviceIndex;
	UPROPERTY(BlueprintReadWrite) int32 SensorIndex;
	UPROPERTY(BlueprintReadWrite) FString SensorType;

	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
