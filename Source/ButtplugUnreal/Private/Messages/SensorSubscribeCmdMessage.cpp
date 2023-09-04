// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/SensorSubscribeCmdMessage.h"

FString USensorSubscribeCmdMessage::GetMessageName()
{
	return TEXT("SensorSubscribeCmd");
}

TSharedPtr<FJsonObject> USensorSubscribeCmdMessage::Serialize()
{
	const auto JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", DeviceIndex);
	JsonObject->SetNumberField("SensorIndex", SensorIndex);
	JsonObject->SetStringField("SensorType", SensorType);

	return JsonObject;
}

void USensorSubscribeCmdMessage::Deserialize(TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);

	DeviceIndex = JsonObject->GetNumberField("DeviceIndex");
	SensorIndex = JsonObject->GetNumberField("SensorIndex");
	SensorType = JsonObject->GetStringField("SensorType");
}
