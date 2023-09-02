// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "DeviceRemovedMessage.generated.h"

/**
 * DeviceRemoved Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/enumeration#deviceremoved
 */
UCLASS()
class BUTTPLUGUNREAL_API UDeviceRemovedMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly) int32 DeviceIndex;
	
	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
