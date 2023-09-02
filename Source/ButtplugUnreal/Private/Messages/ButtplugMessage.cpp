// Copyright 2023 @Cinder. Licensed MIT.


#include "Messages/ButtplugMessage.h"

FString UButtplugMessage::GetMessageNameFromString(const FString& Message)
{
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);

	TSharedPtr<FJsonValue> JsonValue;
	FJsonSerializer::Deserialize(Reader, JsonValue);

	if (!JsonValue.IsValid())
	{
		return "";
	}

	const TMap<FString, TSharedPtr<FJsonValue>> Values = JsonValue->AsArray()[0]->AsObject()->Values;

	TArray<FString> Keys;
	Values.GetKeys(Keys);
	
	return Keys[0];
}

FString UButtplugMessage::GetMessageName()
{
	return TEXT("ButtplugMessage");
}

TSharedPtr<FJsonObject> UButtplugMessage::Serialize()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetNumberField("Id", Id);
	return JsonObject;
}

void UButtplugMessage::Deserialize(const TSharedPtr<FJsonObject> JsonObject)
{
	Id = JsonObject->GetNumberField("Id");
}

FString UButtplugMessage::SerializeToStringWrapped()
{
	return FString::Printf(TEXT("[%s]"), *SerializeToString());
}

FString UButtplugMessage::SerializeToString()
{
	const TSharedPtr<FJsonObject> Message = SerializeNamed();
	
	FString JsonString;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);

	FJsonSerializer::Serialize(Message.ToSharedRef(), Writer);

	return JsonString;
}

void UButtplugMessage::DeserializeFromString(const FString& JsonString)
{
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	TSharedPtr<FJsonValue> JsonValue;
	FJsonSerializer::Deserialize(Reader, JsonValue);

	if (!JsonValue.IsValid())
	{
		return;
	}

	const TMap<FString, TSharedPtr<FJsonValue>> Values = JsonValue->AsArray()[0]->AsObject()->Values;

	TArray<FString> Keys;
	Values.GetKeys(Keys);
	
	Deserialize(Values[Keys[0]]->AsObject());
}

TSharedPtr<FJsonObject> UButtplugMessage::SerializeNamed()
{
	TSharedPtr<FJsonObject> Message = MakeShareable(new FJsonObject());
	Message->SetObjectField(GetMessageName(), Serialize());
	return Message;
}