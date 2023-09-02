// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/StopDeviceCmdMessage.h"

FString UStopDeviceCmdMessage::GetMessageName()
{
	return TEXT("StopDeviceCmd");
}

TSharedPtr<FJsonObject> UStopDeviceCmdMessage::Serialize()
{
	TSharedPtr<FJsonObject> Object = MakeShared<FJsonObject>();
	Object->SetNumberField(TEXT("Id"), Id);
	Object->SetNumberField(TEXT("DeviceIndex"), DeviceIndex);
	return Object;
}

void UStopDeviceCmdMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Id = JsonObject->GetNumberField(TEXT("Id"));
	DeviceIndex = JsonObject->GetNumberField(TEXT("DeviceIndex"));
}
