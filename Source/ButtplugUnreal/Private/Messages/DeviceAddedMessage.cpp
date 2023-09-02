// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/DeviceAddedMessage.h"

FString UDeviceAddedMessage::GetMessageName()
{
	return TEXT("DeviceAdded");
}

TSharedPtr<FJsonObject> UDeviceAddedMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", Device.DeviceIndex);
	JsonObject->SetStringField("DeviceName", Device.DeviceName);
	
	return JsonObject;
}

void UDeviceAddedMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);

	Device.DeviceIndex = JsonObject->GetNumberField("DeviceIndex");
	Device.DeviceName = JsonObject->GetStringField("DeviceName");
}
