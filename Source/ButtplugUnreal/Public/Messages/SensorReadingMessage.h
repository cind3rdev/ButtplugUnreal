// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "SensorReadingMessage.generated.h"

/**
 * SensorReading Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/sensors/#sensorreading
 */
UCLASS()
class BUTTPLUGUNREAL_API USensorReadingMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly) int32 DeviceIndex;
	UPROPERTY(BlueprintReadOnly) int32 SensorIndex;
	UPROPERTY(BlueprintReadOnly) FString SensorType;
	UPROPERTY(BlueprintReadOnly) TArray<int32> Data;

	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
