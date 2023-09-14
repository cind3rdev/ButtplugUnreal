// Copyright 2023 @cind3rdev. See LICENSE.md for more info.


#include "Messages/DeviceRemovedMessage.h"

FString UDeviceRemovedMessage::GetMessageName()
{
	return TEXT("DeviceRemoved");
}

TSharedPtr<FJsonObject> UDeviceRemovedMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", DeviceIndex);

	return JsonObject;
}

void UDeviceRemovedMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);

	DeviceIndex = JsonObject->GetNumberField("DeviceIndex");
}
