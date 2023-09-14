// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "ServerInfoMessage.generated.h"

/**
 * ServerInfo Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/identification#serverinfo
 */
UCLASS()
class BUTTPLUGUNREAL_API UServerInfoMessage : public UButtplugMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly) FString ServerName;
	UPROPERTY(BlueprintReadOnly) int32 MessageVersion;
	UPROPERTY(BlueprintReadOnly) int32 MaxPingTime;
	
	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
