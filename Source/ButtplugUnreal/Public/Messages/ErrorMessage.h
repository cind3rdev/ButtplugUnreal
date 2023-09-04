// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "ErrorMessage.generated.h"

/**
 * Error Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/status/#error
 */
UCLASS()
class BUTTPLUGUNREAL_API UErrorMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	FString ErrorMessage;
	int32 ErrorCode;

	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
