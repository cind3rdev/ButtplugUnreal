// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/SensorReadCmdMessage.h"

FString USensorReadCmdMessage::GetMessageName()
{
	return TEXT("SensorReadCmd");
}

TSharedPtr<FJsonObject> USensorReadCmdMessage::Serialize()
{
	const auto JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", DeviceIndex);
	JsonObject->SetNumberField("SensorIndex", SensorIndex);
	JsonObject->SetStringField("SensorType", SensorType);

	return JsonObject;
}

void USensorReadCmdMessage::Deserialize(TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);

	DeviceIndex = JsonObject->GetNumberField("DeviceIndex");
	SensorIndex = JsonObject->GetNumberField("SensorIndex");
	SensorType = JsonObject->GetStringField("SensorType");
}
