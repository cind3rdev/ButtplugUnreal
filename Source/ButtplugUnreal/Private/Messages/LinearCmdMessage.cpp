// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/LinearCmdMessage.h"

FString ULinearCmdMessage::GetMessageName()
{
	return TEXT("LinearCmd");
}

TSharedPtr<FJsonObject> ULinearCmdMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = Super::Serialize();

	JsonObject->SetNumberField("DeviceIndex", DeviceIndex);

	TArray<TSharedPtr<FJsonValue>> VectorArray;
	
	for (const auto [Index, Duration, Position] : Vectors)
	{
		const TSharedPtr<FJsonObject> VectorObject = MakeShareable(new FJsonObject());
		VectorObject->SetNumberField("Index", Index);
		VectorObject->SetNumberField("Duration", Duration);
		VectorObject->SetNumberField("Position", Position);
		VectorArray.Add(MakeShareable(new FJsonValueObject(VectorObject)));
	}

	JsonObject->SetArrayField("Vectors", VectorArray);

	return JsonObject;
}

void ULinearCmdMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Super::Deserialize(JsonObject);
	DeviceIndex = JsonObject->GetNumberField("DeviceIndex");

	TArray<TSharedPtr<FJsonValue>> VectorArray = JsonObject->GetArrayField("Scalars");

	for (const auto VectorJsonValue : VectorArray)
	{
		const TSharedPtr<FJsonObject> VectorJsonObject = VectorJsonValue->AsObject();
		FButtplugVector Vector = FButtplugVector();
		Vector.Index = VectorJsonObject->GetNumberField("Index");
		Vector.Duration = VectorJsonObject->GetNumberField("Duration");
		Vector.Position = VectorJsonObject->GetNumberField("Position");
		Vectors.Add(Vector);
	}
}
