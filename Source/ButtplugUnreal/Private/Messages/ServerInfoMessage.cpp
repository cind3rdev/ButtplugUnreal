// Copyright 2023 @cind3rdev. See LICENSE.md for more info.


#include "Messages/ServerInfoMessage.h"

FString UServerInfoMessage::GetMessageName()
{
	return TEXT("ServerInfo");
}

TSharedPtr<FJsonObject> UServerInfoMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();

	JsonObject->SetStringField(TEXT("ServerName"), ServerName);
	JsonObject->SetNumberField(TEXT("MessageVersion"), MessageVersion);
	JsonObject->SetNumberField(TEXT("MaxPingTime"), MaxPingTime);

	return JsonObject;
}

void UServerInfoMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);

	ServerName = JsonObject->GetStringField(TEXT("ServerName"));
	MessageVersion = JsonObject->GetIntegerField(TEXT("MessageVersion"));
	MaxPingTime = JsonObject->GetIntegerField(TEXT("MaxPingTime"));
}
