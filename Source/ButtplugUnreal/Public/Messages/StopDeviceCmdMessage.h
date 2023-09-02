// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "StopDeviceCmdMessage.generated.h"

/**
 * StopDeviceCmd Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/generic#stopdevicecmd
 */
UCLASS()
class BUTTPLUGUNREAL_API UStopDeviceCmdMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) int32 DeviceIndex;
	
	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
