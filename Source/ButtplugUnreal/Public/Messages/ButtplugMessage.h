// Copyright 2023 @cind3rdev. See LICENSE.md for more info.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ButtplugMessage.generated.h"

/**
 * ButtplugMessage is the root-level message class which is used to serialize and deserialize
 * Buttplug messages to and from JSON.
 */
UCLASS()
class BUTTPLUGUNREAL_API UButtplugMessage : public UObject
{
	GENERATED_BODY()

public:
	uint32 Id = 1;
	
	virtual FString GetMessageName();
	virtual TSharedPtr<FJsonObject> Serialize();
	virtual void Deserialize(TSharedPtr<FJsonObject> JsonObject);

	TSharedPtr<FJsonObject> SerializeNamed();
	FString SerializeToStringWrapped();
	FString SerializeToString();
	void DeserializeFromString(const FString& JsonString);

	static FString GetMessageNameFromString(const FString& Message);
};
