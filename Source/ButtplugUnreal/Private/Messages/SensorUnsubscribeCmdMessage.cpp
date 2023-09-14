// Copyright 2023 @cind3rdev. See LICENSE.md for more info.


#include "Messages/SensorUnsubscribeCmdMessage.h"

FString USensorUnsubscribeCmdMessage::GetMessageName()
{
	return TEXT("SensorUnsubscribeCmd");
}

TSharedPtr<FJsonObject> USensorUnsubscribeCmdMessage::Serialize()
{
	const auto JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", DeviceIndex);
	JsonObject->SetNumberField("SensorIndex", SensorIndex);
	JsonObject->SetStringField("SensorType", SensorType);

	return JsonObject;
}

void USensorUnsubscribeCmdMessage::Deserialize(TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);

	DeviceIndex = JsonObject->GetNumberField("DeviceIndex");
	SensorIndex = JsonObject->GetNumberField("SensorIndex");
	SensorType = JsonObject->GetStringField("SensorType");
}
