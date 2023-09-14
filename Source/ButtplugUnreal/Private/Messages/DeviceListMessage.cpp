// Copyright 2023 @cind3rdev. See LICENSE.md for more info.


#include "Messages/DeviceListMessage.h"

FString UDeviceListMessage::GetMessageName()
{
	return TEXT("DeviceList");
}

TSharedPtr<FJsonObject> UDeviceListMessage::Serialize()
{
	const TSharedPtr<FJsonObject> JsonObject = Super::Serialize();
	TArray<TSharedPtr<FJsonValue>> DeviceArray;

	for (auto [DeviceName, DeviceIndex, DeviceDisplayName] : Devices)
	{
		TSharedPtr<FJsonObject> DeviceObject = MakeShareable(new FJsonObject());
		DeviceObject->SetStringField("DeviceName", DeviceName);
		DeviceObject->SetNumberField("DeviceIndex", DeviceIndex);
		DeviceObject->SetStringField("DeviceDisplayName", DeviceDisplayName);
		DeviceArray.Add(MakeShareable(new FJsonValueObject(DeviceObject)));
	}
	
	JsonObject->SetArrayField("Devices", DeviceArray);

	return JsonObject;
}

void UDeviceListMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);
	const TArray<TSharedPtr<FJsonValue>> DeviceArray = JsonObject->GetArrayField("Devices");

	for (const auto& Device : DeviceArray)
	{
		const TSharedPtr<FJsonObject> DeviceObject = Device->AsObject();
		FString DeviceName = DeviceObject->GetStringField("DeviceName");
		const uint32 DeviceIndex = DeviceObject->GetNumberField("DeviceIndex");
		FString DeviceDisplayName = DeviceObject->GetStringField("DeviceDisplayName");
		FButtplugDevice ButtplugDevice;
		ButtplugDevice.DeviceName = DeviceName;
		ButtplugDevice.DeviceIndex = DeviceIndex;
		ButtplugDevice.DeviceDisplayName = DeviceDisplayName;
		Devices.Add(ButtplugDevice);
	}
}
