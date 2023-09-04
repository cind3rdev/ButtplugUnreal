﻿// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "SensorReadCmdMessage.generated.h"

/**
 * SensorReadCmd Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/sensors/#sensorreadcmd
 */
UCLASS()
class BUTTPLUGUNREAL_API USensorReadCmdMessage : public UButtplugMessage
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
