// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugMessage.h"
#include "RequestServerInfoMessage.generated.h"

/**
 * RequestServerInfo Message
 * https://buttplug-spec.docs.buttplug.io/docs/spec/identification#requestserverinfo
 */
UCLASS()
class BUTTPLUGUNREAL_API URequestServerInfoMessage : public UButtplugMessage
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite) FString ClientName = TEXT("Client Name");
	UPROPERTY(BlueprintReadWrite) int32 MessageVersion = 1;
	
	virtual FString GetMessageName() override;
	virtual TSharedPtr<FJsonObject> Serialize() override;
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject) override;
};
