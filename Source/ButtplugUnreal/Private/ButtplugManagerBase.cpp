// Copyright 2023 @Cinder. Licensed MIT.

#include "..\Public\ButtplugManagerBase.h"
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

void UButtplugManagerBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Automatically clean up the WebSocket when the component is destroyed.
	Shutdown();
	return Super::EndPlay(EndPlayReason);
}

void UButtplugManagerBase::Connect()
{
	EnsureModuleLoaded("WebSockets");
	EnsureModuleLoaded("Json");
	EnsureModuleLoaded("JsonUtilities");

	this->WebSocket = FWebSocketsModule::Get().CreateWebSocket(ServerAddress);

	WebSocket->OnConnected().AddUObject(this, &UButtplugManagerBase::OnWebSocketConnected);
	WebSocket->OnMessage().AddUObject(this, &UButtplugManagerBase::OnWebSocketMessage);
	WebSocket->OnConnectionError().AddUObject(this, &UButtplugManagerBase::OnWebSocketConnectionError);
	WebSocket->OnClosed().AddUObject(this, &UButtplugManagerBase::OnWebSocketClosed);

	WebSocket->Connect();
}

void UButtplugManagerBase::Shutdown()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(PingTimerHandler);
	Devices.Empty();
	
	if (WebSocket && WebSocket->IsConnected())
	{
		StopAllDevices();
		WebSocket->Close();
	}
}

bool UButtplugManagerBase::IsConnected()
{
	return WebSocket && WebSocket->IsConnected();
}

void UButtplugManagerBase::StartScanning()
{
	if (!IsConnected()) return;

	const auto StartScanningMessage = NewObject<UStartScanningMessage>();

	SendMessage(StartScanningMessage);
}

void UButtplugManagerBase::StopScanning()
{
	if (!IsConnected()) return;
	
	const auto StopScanningMessage = NewObject<UStopScanningMessage>();

	SendMessage(StopScanningMessage);
}

void UButtplugManagerBase::RequestServerInfo()
{
	if (!IsConnected()) return;
	
	const auto RequestServerInfoMessage = NewObject<URequestServerInfoMessage>();

	SendMessage(RequestServerInfoMessage);
}

void UButtplugManagerBase::RequestDeviceList()
{
	if (!IsConnected()) return;
	
	const auto RequestDeviceListMessage = NewObject<URequestDeviceListMessage>();

	SendMessage(RequestDeviceListMessage);
}

void UButtplugManagerBase::BasicVibrate(const int32 DeviceIndex, const float Speed)
{
	if (!IsConnected()) return;
	
	FButtplugSpeed S;
	S.Index = 0;
	S.Speed = Speed;

	VibrateCmd(DeviceIndex, {S});
}

void UButtplugManagerBase::StopAllDevices()
{
	if (!IsConnected()) return;
	
	const auto StopAllDevicesMessage = NewObject<UStopAllDevicesMessage>();

	SendMessage(StopAllDevicesMessage);
}

void UButtplugManagerBase::StopDeviceCmd(const int32 DeviceIndex)
{
	if (!IsConnected()) return;
	
	const auto StopDeviceCmdMessage = NewObject<UStopDeviceCmdMessage>();
	StopDeviceCmdMessage->DeviceIndex = DeviceIndex;

	SendMessage(StopDeviceCmdMessage);
}

void UButtplugManagerBase::SensorReadCmd(const int32 DeviceIndex, const int32 SensorIndex, FString SensorType)
{
	if (!IsConnected()) return;

	const auto SensorReadCmdMessage = NewObject<USensorReadCmdMessage>();
	SensorReadCmdMessage->DeviceIndex = DeviceIndex;
	SensorReadCmdMessage->SensorIndex = SensorIndex;
	SensorReadCmdMessage->SensorType = SensorType;

	SendMessage(SensorReadCmdMessage);
}

void UButtplugManagerBase::SensorSubscribeCmd(const int32 DeviceIndex, const int32 SensorIndex, FString SensorType)
{
	if (!IsConnected()) return;

	const auto SensorSubscribeCmdMessage = NewObject<USensorSubscribeCmdMessage>();
	SensorSubscribeCmdMessage->DeviceIndex = DeviceIndex;
	SensorSubscribeCmdMessage->SensorIndex = SensorIndex;
	SensorSubscribeCmdMessage->SensorType = SensorType;

	SendMessage(SensorSubscribeCmdMessage);
}

void UButtplugManagerBase::SensorUnsubscribeCmd(const int32 DeviceIndex, const int32 SensorIndex, FString SensorType)
{
	if (!IsConnected()) return;

	const auto SensorUnsubscribeCmdMessage = NewObject<USensorUnsubscribeCmdMessage>();
	SensorUnsubscribeCmdMessage->DeviceIndex = DeviceIndex;
	SensorUnsubscribeCmdMessage->SensorIndex = SensorIndex;
	SensorUnsubscribeCmdMessage->SensorType = SensorType;

	SendMessage(SensorUnsubscribeCmdMessage);
}

void UButtplugManagerBase::ScalarCmd(const int32 DeviceIndex, const TArray<FButtplugScalar> Scalars)
{
	if (!IsConnected()) return;
	
	const auto ScalarCmdMessage = NewObject<UScalarCmdMessage>();
	ScalarCmdMessage->DeviceIndex = DeviceIndex;
	ScalarCmdMessage->Scalars = Scalars;

	SendMessage(ScalarCmdMessage);
}

void UButtplugManagerBase::VibrateCmd(const int32 DeviceIndex, const TArray<FButtplugSpeed> Speeds)
{
	if (!IsConnected()) return;

	const auto VibrateCmdMessage = NewObject<UVibrateCmdMessage>();
	VibrateCmdMessage->DeviceIndex = DeviceIndex;
	VibrateCmdMessage->Speeds = Speeds;

	SendMessage(VibrateCmdMessage);
}

void UButtplugManagerBase::LinearCmd(const int32 DeviceIndex, const TArray<FButtplugVector> Vectors)
{
	if (!IsConnected()) return;

	const auto LinearCmdMessage = NewObject<ULinearCmdMessage>();
	LinearCmdMessage->DeviceIndex = DeviceIndex;
	LinearCmdMessage->Vectors = Vectors;

	SendMessage(LinearCmdMessage);
}

void UButtplugManagerBase::RotateCmd(const int32 DeviceIndex, const TArray<FButtplugRotation> Rotations)
{
	if (!IsConnected()) return;

	const auto RotateCmdMessage = NewObject<URotateCmdMessage>();
	RotateCmdMessage->DeviceIndex = DeviceIndex;
	RotateCmdMessage->Rotations = Rotations;

	SendMessage(RotateCmdMessage);
}

void UButtplugManagerBase::OnWebSocketClosed(const int32 StatusCode, const FString& Reason, const bool WasClean)
{
	OnDisconnected.Broadcast(StatusCode, Reason, WasClean);
}

void UButtplugManagerBase::OnWebSocketConnected()
{
	if (!IsConnected()) return;
	
	RequestServerInfo();
}

void UButtplugManagerBase::OnWebSocketConnectionError(const FString& Error)
{
	OnWebSocketError.Broadcast(Error);
	OnError.Broadcast(Error);
}

void UButtplugManagerBase::OnWebSocketMessage(const FString& Message)
{
	if (!IsConnected()) return;
	
	const auto MessageName = UButtplugMessage::GetMessageNameFromString(Message);
	
	if (MessageName == "ServerInfo")
	{
		const auto ServerInfoMessage = NewObject<UServerInfoMessage>();
		ServerInfoMessage->DeserializeFromString(Message);
		
		OnConnected.Broadcast();

		// Start Ping Timer
		GetOwner()->GetWorldTimerManager().SetTimer(PingTimerHandler, this, &UButtplugManagerBase::Ping, ServerInfoMessage->MaxPingTime / 2, true);

		// Request device list
		RequestDeviceList();
	}
	else if (MessageName == "DeviceAdded")
	{
		const auto DeviceAddedMessage = NewObject<UDeviceAddedMessage>();
		DeviceAddedMessage->DeserializeFromString(Message);

		Devices.Add(DeviceAddedMessage->Device);
		
		OnDeviceAdded.Broadcast(DeviceAddedMessage->Device);
		OnDevicesUpdated.Broadcast();
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
		
		OnDeviceRemoved.Broadcast(DeviceRemovedMessage->DeviceIndex);
		OnDevicesUpdated.Broadcast();
	}
	else if (MessageName == "DeviceList")
	{
		const auto DeviceListMessage = NewObject<UDeviceListMessage>();
		DeviceListMessage->DeserializeFromString(Message);

		for (auto Device : DeviceListMessage->Devices)
		{
			Devices.Add(Device);
			OnDeviceAdded.Broadcast(Device);
		}
		
		OnDevicesUpdated.Broadcast();
	}
	else if (MessageName == "ScanningFinished")
	{
		const auto ScanningFinishedMessage = NewObject<UScanningFinishedMessage>();
		ScanningFinishedMessage->DeserializeFromString(Message);

		OnScanningFinished.Broadcast();
	}
	else if (MessageName == "SenorReading")
	{
		const auto SensorReadingMessage = NewObject<USensorReadingMessage>();
		SensorReadingMessage->DeserializeFromString(Message);

		OnSensorReading.Broadcast(SensorReadingMessage);
	}
	else if (MessageName == "Error")
	{
		const auto ErrorMessage = NewObject<UErrorMessage>();
		ErrorMessage->DeserializeFromString(Message);

		OnButtplugError.Broadcast(ErrorMessage);
		OnError.Broadcast(ErrorMessage->ErrorMessage);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("[ButtplugUnreal] Received Message: %s"), *Message)
	}
}

void UButtplugManagerBase::SendMessage(UButtplugMessage* Message)
{
	if (!IsConnected()) return;
	
	const FString SerializedMessage = Message->SerializeToStringWrapped();
	UE_LOG(LogTemp, Display, TEXT("[ButtplugUnreal] Sending Message: %s"), *SerializedMessage);
	WebSocket->Send(SerializedMessage);
}

void UButtplugManagerBase::Ping()
{
	UPingMessage *PingMessage = NewObject<UPingMessage>();
	SendMessage(PingMessage);
}

void UButtplugManagerBase::EnsureModuleLoaded(const FString& ModuleName)
{
	if (!FModuleManager::Get().IsModuleLoaded(FName(ModuleName)))
	{
		UE_LOG(LogTemp, Warning, TEXT("[ButtplugUnreal] %s module not loaded. Attempting to load."), *ModuleName);
		FModuleManager::Get().LoadModule(FName(ModuleName));
	}
}
