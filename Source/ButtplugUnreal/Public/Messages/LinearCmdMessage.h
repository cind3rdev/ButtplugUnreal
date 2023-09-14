// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "ButtplugVector.h"
#include "LinearCmdMessage.generated.h"

/**
 * LinearCmd Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/generic#linearcmd
 */
UCLASS()
class BUTTPLUGUNREAL_API ULinearCmdMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	int32 DeviceIndex;
	TArray<FButtplugVector> Vectors;

	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
