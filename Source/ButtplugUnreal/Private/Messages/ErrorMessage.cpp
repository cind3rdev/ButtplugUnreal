// Copyright 2023 @cind3rdev. See LICENSE.md for more info.


#include "Messages/ErrorMessage.h"

FString UErrorMessage::GetMessageName()
{
	return TEXT("Error");
}

TSharedPtr<FJsonObject> UErrorMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();

	JsonObject->SetStringField("ErrorMessage", ErrorMessage);
	JsonObject->SetNumberField("ErrorCode", ErrorCode);

	return JsonObject;
}

void UErrorMessage::Deserialize(TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);

	ErrorMessage = JsonObject->GetStringField("ErrorMessage");
	ErrorCode = JsonObject->GetNumberField("ErrorCode");
}
