// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/VibrateCmdMessage.h"


FString UVibrateCmdMessage::GetMessageName()
{
	return TEXT("VibrateCmd");
}

TSharedPtr<FJsonObject> UVibrateCmdMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", DeviceIndex);

	TArray<TSharedPtr<FJsonValue>> ScalarArray;
	
	for (auto [Index, Speed] : Speeds)
	{
		const TSharedPtr<FJsonObject> ScalarObject = MakeShareable(new FJsonObject());
		ScalarObject->SetNumberField("Index", Index);
		ScalarObject->SetNumberField("Speed", Speed);
		ScalarArray.Add(MakeShareable(new FJsonValueObject(ScalarObject)));
	}

	JsonObject->SetArrayField("Speeds", ScalarArray);

	return JsonObject;
}

void UVibrateCmdMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);
	DeviceIndex = JsonObject->GetNumberField("DeviceIndex");

	TArray<TSharedPtr<FJsonValue>> ScalarArray = JsonObject->GetArrayField("Speeds");

	for (const auto ScalarJsonValue : ScalarArray)
	{
		const TSharedPtr<FJsonObject> ScalarJsonObject = ScalarJsonValue->AsObject();
		FButtplugSpeed Speed = FButtplugSpeed();
		Speed.Index = ScalarJsonObject->GetNumberField("Index");
		Speed.Speed = ScalarJsonObject->GetNumberField("Speed");
		Speeds.Add(Speed);
	}
}