// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/RequestServerInfoMessage.h"

FString URequestServerInfoMessage::GetMessageName()
{
	return TEXT("RequestServerInfo");
}

TSharedPtr<FJsonObject> URequestServerInfoMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();
	JsonObject->SetStringField("ClientName", ClientName);
	JsonObject->SetNumberField("MessageVersion", MessageVersion);
	return JsonObject;
}

void URequestServerInfoMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);
	ClientName = JsonObject->GetStringField("ClientName");
	MessageVersion = JsonObject->GetNumberField("MessageVersion");
}