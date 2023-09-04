// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/SensorReadingMessage.h"

FString USensorReadingMessage::GetMessageName()
{
	return TEXT("SensorReading");
}

TSharedPtr<FJsonObject> USensorReadingMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", DeviceIndex);
	JsonObject->SetNumberField("SensorIndex", SensorIndex);
	JsonObject->SetStringField("SensorType", SensorType);

	TArray<TSharedPtr<FJsonValueNumber>> DataArray;

	for (const auto DataItem : Data)
	{
		DataArray.Add(MakeShareable(new FJsonValueNumber(DataItem)));
	}

	return JsonObject;
}

void USensorReadingMessage::Deserialize(TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);

	DeviceIndex = JsonObject->GetNumberField("DeviceIndex");
	SensorIndex = JsonObject->GetNumberField("SensorIndex");
	SensorType = JsonObject->GetStringField("SensorType");

	const auto DataArray = JsonObject->GetArrayField("Data");

	for (const auto DataValue : DataArray)
	{
		Data.Add(DataValue->AsNumber());
	}
}
