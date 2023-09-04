// Copyright 2023 @Cinder. Licensed MIT.

#include "ButtplugManager.h"
#include "IWebSocket.h"
#include "Messages/RequestServerInfoMessage.h"
#include "WebSocketsModule.h"
#include "Messages/DeviceListMessage.h"
#include "Messages/DeviceRemovedMessage.h"
#include "Messages/LinearCmdMessage.h"
#include "Messages/PingMessage.h"
#include "Messages/RequestDeviceListMessage.h"
#include "Messages/RotateCmdMessage.h"
#include "Messages/ScalarCmdMessage.h"
#include "Messages/ScanningFinishedMessage.h"
#include "Messages/SensorReadCmdMessage.h"
#include "Messages/SensorReadingMessage.h"
#include "Messages/SensorSubscribeCmdMessage.h"
#include "Messages/SensorUnsubscribeCmdMessage.h"
#include "Messages/ServerInfoMessage.h"
#include "Messages/StartScanningMessage.h"
#include "Messages/StopAllDevicesMessage.h"
#include "Messages/StopDeviceCmdMessage.h"
#include "Messages/StopScanningMessage.h"
#include "Messages/VibrateCmdMessage.h"

void UButtplugManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Automatically clean up the WebSocket when the component is destroyed.
	Shutdown();
	return Super::EndPlay(EndPlayReason);
}

void UButtplugManager::Connect()
{
	EnsureModuleLoaded("WebSockets");
	EnsureModuleLoaded("Json");
	EnsureModuleLoaded("JsonUtilities");

	this->WebSocket = FWebSocketsModule::Get().CreateWebSocket(ServerAddress);

	BindWebSocketEvents();

	WebSocket->Connect();
}

void UButtplugManager::Shutdown()
{
	if (!WebSocket->IsConnected()) return;
	
	GetOwner()->GetWorldTimerManager().ClearTimer(PingTimerHandler);
	StopAllDevices();
	Devices.Empty();
	WebSocket->Close();
}

bool UButtplugManager::IsConnected()
{
	return WebSocket->IsConnected();
}

void UButtplugManager::StartScanning()
{
	if (!WebSocket->IsConnected()) return;

	const auto StartScanningMessage = NewObject<UStartScanningMessage>();

	SendMessage(StartScanningMessage);
}

void UButtplugManager::StopScanning()
{
	if (!WebSocket->IsConnected()) return;
	
	const auto StopScanningMessage = NewObject<UStopScanningMessage>();

	SendMessage(StopScanningMessage);
}

void UButtplugManager::RequestServerInfo()
{
	if (!WebSocket->IsConnected()) return;
	
	const auto RequestServerInfoMessage = NewObject<URequestServerInfoMessage>();

	SendMessage(RequestServerInfoMessage);
}

void UButtplugManager::RequestDeviceList()
{
	if (!WebSocket->IsConnected()) return;
	
	const auto RequestDeviceListMessage = NewObject<URequestDeviceListMessage>();

	SendMessage(RequestDeviceListMessage);
}

void UButtplugManager::BasicVibrate(const int32 DeviceIndex, const float Speed) const
{
	if (!WebSocket->IsConnected()) return;
	
	FButtplugSpeed S;
	S.Index = 0;
	S.Speed = Speed;

	VibrateCmd(DeviceIndex, {S});
}

void UButtplugManager::StopAllDevices()
{
	if (!WebSocket->IsConnected()) return;
	
	const auto StopAllDevicesMessage = NewObject<UStopAllDevicesMessage>();

	SendMessage(StopAllDevicesMessage);
}

void UButtplugManager::StopDeviceCmd(const int32 DeviceIndex) const
{
	if (!WebSocket->IsConnected()) return;
	
	const auto StopDeviceCmdMessage = NewObject<UStopDeviceCmdMessage>();
	StopDeviceCmdMessage->DeviceIndex = DeviceIndex;

	SendMessage(StopDeviceCmdMessage);
}

void UButtplugManager::SensorReadCmd(const int32 DeviceIndex, const int32 SensorIndex, FString SensorType) const
{
	if (!WebSocket->IsConnected()) return;

	const auto SensorReadCmdMessage = NewObject<USensorReadCmdMessage>();
	SensorReadCmdMessage->DeviceIndex = DeviceIndex;
	SensorReadCmdMessage->SensorIndex = SensorIndex;
	SensorReadCmdMessage->SensorType = SensorType;

	SendMessage(SensorReadCmdMessage);
}

void UButtplugManager::SensorSubscribeCmd(const int32 DeviceIndex, const int32 SensorIndex, FString SensorType) const
{
	if (!WebSocket->IsConnected()) return;

	const auto SensorSubscribeCmdMessage = NewObject<USensorSubscribeCmdMessage>();
	SensorSubscribeCmdMessage->DeviceIndex = DeviceIndex;
	SensorSubscribeCmdMessage->SensorIndex = SensorIndex;
	SensorSubscribeCmdMessage->SensorType = SensorType;

	SendMessage(SensorSubscribeCmdMessage);
}

void UButtplugManager::SensorUnsubscribeCmd(const int32 DeviceIndex, const int32 SensorIndex, FString SensorType) const
{
	if (!WebSocket->IsConnected()) return;

	const auto SensorUnsubscribeCmdMessage = NewObject<USensorUnsubscribeCmdMessage>();
	SensorUnsubscribeCmdMessage->DeviceIndex = DeviceIndex;
	SensorUnsubscribeCmdMessage->SensorIndex = SensorIndex;
	SensorUnsubscribeCmdMessage->SensorType = SensorType;

	SendMessage(SensorUnsubscribeCmdMessage);
}

void UButtplugManager::ScalarCmd(const int32 DeviceIndex, const TArray<FButtplugScalar> Scalars) const
{
	if (!WebSocket->IsConnected()) return;
	
	const auto ScalarCmdMessage = NewObject<UScalarCmdMessage>();
	ScalarCmdMessage->DeviceIndex = DeviceIndex;
	ScalarCmdMessage->Scalars = Scalars;

	SendMessage(ScalarCmdMessage);
}

void UButtplugManager::VibrateCmd(const int32 DeviceIndex, const TArray<FButtplugSpeed> Speeds) const
{
	if (!WebSocket->IsConnected()) return;

	const auto VibrateCmdMessage = NewObject<UVibrateCmdMessage>();
	VibrateCmdMessage->DeviceIndex = DeviceIndex;
	VibrateCmdMessage->Speeds = Speeds;

	SendMessage(VibrateCmdMessage);
}

void UButtplugManager::LinearCmd(const int32 DeviceIndex, const TArray<FButtplugVector> Vectors) const
{
	if (!WebSocket->IsConnected()) return;

	const auto LinearCmdMessage = NewObject<ULinearCmdMessage>();
	LinearCmdMessage->DeviceIndex = DeviceIndex;
	LinearCmdMessage->Vectors = Vectors;

	SendMessage(LinearCmdMessage);
}

void UButtplugManager::RotateCmd(const int32 DeviceIndex, const TArray<FButtplugRotation> Rotations) const
{
	if (!WebSocket->IsConnected()) return;

	const auto RotateCmdMessage = NewObject<URotateCmdMessage>();
	RotateCmdMessage->DeviceIndex = DeviceIndex;
	RotateCmdMessage->Rotations = Rotations;

	SendMessage(RotateCmdMessage);
}

void UButtplugManager::BindWebSocketEvents()
{
	WebSocket->OnConnected().AddLambda([this]() -> void
	{
		RequestServerInfo();
	});

	WebSocket->OnConnectionError().AddLambda([this](const FString& Error) -> void
	{
		OnWebSocketError(Error);
		OnError(Error);
	});

	WebSocket->OnClosed().AddLambda([this](const int32 StatusCode, const FString& Reason, const bool WasClean) -> void
	{
		OnDisconnected(StatusCode, Reason, WasClean);
	});

	WebSocket->OnMessage().AddLambda([this](const FString& Message) -> void
	{
		HandleIncomingMessage(Message);
	});
}

void UButtplugManager::HandleIncomingMessage(const FString& Message)
{
	const auto MessageName = UButtplugMessage::GetMessageNameFromString(Message);

	if (MessageName == "ServerInfo")
	{
		const auto ServerInfoMessage = NewObject<UServerInfoMessage>();
		ServerInfoMessage->DeserializeFromString(Message);
		
		OnConnected();

		// Start Ping Timer
		GetOwner()->GetWorldTimerManager().SetTimer(PingTimerHandler, this, &UButtplugManager::Ping, ServerInfoMessage->MaxPingTime / 2, true);

		// Request device list
		RequestDeviceList();
	}
	else if (MessageName == "DeviceAdded")
	{
		const auto DeviceAddedMessage = NewObject<UDeviceAddedMessage>();
		DeviceAddedMessage->DeserializeFromString(Message);

		Devices.Add(DeviceAddedMessage->Device);
		
		OnDeviceAdded(DeviceAddedMessage->Device);
		OnDevicesChanged();
	}
	else if (MessageName == "DeviceRemoved")
	{
		const auto DeviceRemovedMessage = NewObject<UDeviceRemovedMessage>();
		DeviceRemovedMessage->DeserializeFromString(Message);

		for (int i = 0; i < Devices.Num(); i++)
		{
			if (Devices[i].DeviceIndex == DeviceRemovedMessage->DeviceIndex)
			{
				Devices.RemoveAt(i);
				break;
			}
		}
		
		OnDeviceRemoved(DeviceRemovedMessage->DeviceIndex);
		OnDevicesChanged();
	}
	else if (MessageName == "DeviceList")
	{
		const auto DeviceListMessage = NewObject<UDeviceListMessage>();
		DeviceListMessage->DeserializeFromString(Message);

		for (auto Device : DeviceListMessage->Devices)
		{
			Devices.Add(Device);
			OnDeviceAdded(Device);
		}

		OnDevicesChanged();
	}
	else if (MessageName == "ScanningFinished")
	{
		const auto ScanningFinishedMessage = NewObject<UScanningFinishedMessage>();
		ScanningFinishedMessage->DeserializeFromString(Message);

		OnScanningFinished();
	}
	else if (MessageName == "SenorReading")
	{
		const auto SensorReadingMessage = NewObject<USensorReadingMessage>();
		SensorReadingMessage->DeserializeFromString(Message);

		OnSensorReading(SensorReadingMessage);
	}
	else if (MessageName == "Error")
	{
		const auto ErrorMessage = NewObject<UErrorMessage>();
		ErrorMessage->DeserializeFromString(Message);

		OnButtplugError(ErrorMessage);
		OnError(ErrorMessage->ErrorMessage);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("[ButtplugUnreal] Received Message: %s"), *Message)
	}
}

void UButtplugManager::SendMessage(UButtplugMessage* Message) const
{
	const FString SerializedMessage = Message->SerializeToStringWrapped();
	UE_LOG(LogTemp, Display, TEXT("[ButtplugUnreal] Sending Message: %s"), *SerializedMessage);
	WebSocket->Send(SerializedMessage);
}

void UButtplugManager::Ping() const
{
	UPingMessage *PingMessage = NewObject<UPingMessage>();
	SendMessage(PingMessage);
}

void UButtplugManager::EnsureModuleLoaded(const FString& ModuleName)
{
	if (!FModuleManager::Get().IsModuleLoaded(FName(ModuleName)))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ButtplugUnreal] %s module not loaded. Attempting to load."), *ModuleName);
		FModuleManager::Get().LoadModule(FName(ModuleName));
	}
}
