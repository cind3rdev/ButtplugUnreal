// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "ButtplugDevice.h"
#include "DeviceAddedMessage.generated.h"

/**
 * DeviceAdded Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/enumeration#deviceadded
 */
UCLASS()
class BUTTPLUGUNREAL_API UDeviceAddedMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly) FButtplugDevice Device;

	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
