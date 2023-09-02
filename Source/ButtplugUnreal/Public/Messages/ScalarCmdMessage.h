// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "..\ButtplugScalar.h"
#include "ScalarCmdMessage.generated.h"

/**
 * ScalarCmd Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/generic#scalarcmd
 */
UCLASS()
class BUTTPLUGUNREAL_API UScalarCmdMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) int32 DeviceIndex;
	UPROPERTY(BlueprintReadWrite) TArray<FButtplugScalar> Scalars = TArray<FButtplugScalar>();
	
	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
