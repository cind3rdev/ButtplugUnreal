// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/RotateCmdMessage.h"

FString URotateCmdMessage::GetMessageName()
{
	return TEXT("RotateCmd");
}

TSharedPtr<FJsonObject> URotateCmdMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", DeviceIndex);

	TArray<TSharedPtr<FJsonValue>> RotationArray;
	
	for (const auto [Index, Speed, Clockwise] : Rotations)
	{
		const TSharedPtr<FJsonObject> JsonRotation = MakeShareable(new FJsonObject());
		JsonRotation->SetNumberField("Index", Index);
		JsonRotation->SetNumberField("Speed", Speed);
		JsonRotation->SetBoolField("Clockwise", Clockwise);
		RotationArray.Add(MakeShareable(new FJsonValueObject(JsonRotation)));
	}
	
	return JsonObject;
}

void URotateCmdMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);
	DeviceIndex = JsonObject->GetIntegerField("DeviceIndex");

	TArray<TSharedPtr<FJsonValue>> RotationArray = JsonObject->GetArrayField("Rotations");

	for (const auto RotationJsonValue : RotationArray)
	{
		const TSharedPtr<FJsonObject> RotationJsonObject = RotationJsonValue->AsObject();
		FButtplugRotation Rotation = FButtplugRotation();
		Rotation.Index = RotationJsonObject->GetIntegerField("Index");
		Rotation.Speed = RotationJsonObject->GetNumberField("Speed");
		Rotation.Clockwise = RotationJsonObject->GetBoolField("Clockwise");
		Rotations.Add(Rotation);
	}
}
