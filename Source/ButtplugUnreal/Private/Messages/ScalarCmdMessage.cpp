// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/ScalarCmdMessage.h"

FString UScalarCmdMessage::GetMessageName()
{
	return TEXT("ScalarCmd");
}

TSharedPtr<FJsonObject> UScalarCmdMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", DeviceIndex);

	TArray<TSharedPtr<FJsonValue>> ScalarArray;
	
	for (auto [Index, Scalar, ActuatorType] : Scalars)
	{
		const TSharedPtr<FJsonObject> ScalarObject = MakeShareable(new FJsonObject());
		ScalarObject->SetNumberField("Index", Index);
		ScalarObject->SetNumberField("Scalar", Scalar);
		ScalarObject->SetStringField("ActuatorType", ActuatorType);
		ScalarArray.Add(MakeShareable(new FJsonValueObject(ScalarObject)));
	}

	JsonObject->SetArrayField("Scalars", ScalarArray);

	return JsonObject;
}

void UScalarCmdMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);
	DeviceIndex = JsonObject->GetNumberField("DeviceIndex");

	TArray<TSharedPtr<FJsonValue>> ScalarArray = JsonObject->GetArrayField("Scalars");

	for (const auto ScalarJsonValue : ScalarArray)
	{
		const TSharedPtr<FJsonObject> ScalarJsonObject = ScalarJsonValue->AsObject();
		FButtplugScalar Scalar = FButtplugScalar();
		Scalar.Index = ScalarJsonObject->GetNumberField("Index");
		Scalar.Scalar = ScalarJsonObject->GetNumberField("Scalar");
		Scalar.ActuatorType = ScalarJsonObject->GetStringField("ActuatorType");
		Scalars.Add(Scalar);
	}
}