// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "ButtplugDevice.h"
#include "DeviceListMessage.generated.h"

/**
 * DeviceList Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/enumeration#devicelist
 */
UCLASS()
class BUTTPLUGUNREAL_API UDeviceListMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly) TArray<FButtplugDevice> Devices;
	
	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
