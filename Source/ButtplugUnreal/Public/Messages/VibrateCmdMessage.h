// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "..\ButtplugSpeed.h"
#include "VibrateCmdMessage.generated.h"

/**
 * VibrateCmd Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/deprecated#vibratecmd
 */
UCLASS()
class BUTTPLUGUNREAL_API UVibrateCmdMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) int32 DeviceIndex;
	UPROPERTY(BlueprintReadWrite) TArray<FButtplugSpeed> Speeds = TArray<FButtplugSpeed>();
	
	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(const TSharedPtr<FJsonObject> JsonObject) override;
};
