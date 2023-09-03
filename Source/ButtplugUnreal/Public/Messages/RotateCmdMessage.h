// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "ButtplugRotation.h"
#include "RotateCmdMessage.generated.h"

/**
 * RotateCmd Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/generic#rotatecmd
 */
UCLASS()
class BUTTPLUGUNREAL_API URotateCmdMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	int32 DeviceIndex;
	TArray<FButtplugRotation> Rotations;
	
	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
