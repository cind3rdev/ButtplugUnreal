// Copyright 2023 @Cinder. Licensed MIT.


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
