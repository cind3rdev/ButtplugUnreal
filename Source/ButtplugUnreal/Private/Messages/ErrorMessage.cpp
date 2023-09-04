// Copyright 2023 @Cinder. Licensed MIT.


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
