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

	// Stop ping timer
	GetOwner()->GetWorldTimerManager().ClearTimer(PingTimerHandler);
	
	// Send stop all devices command
	StopAllDevices();

	// Empty devices list (will be re-populated on next connect)
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

	UStartScanningMessage *StartScanningMessage = NewObject<UStartScanningMessage>();

	SendMessage(StartScanningMessage);
}

void UButtplugManager::StopScanning()
{
	if (!WebSocket->IsConnected()) return;
	
	UStopScanningMessage *StopScanningMessage = NewObject<UStopScanningMessage>();

	SendMessage(StopScanningMessage);
}

void UButtplugManager::RequestServerInfo()
{
	if (!WebSocket->IsConnected()) return;
	
	URequestServerInfoMessage *RequestServerInfoMessage = NewObject<URequestServerInfoMessage>();

	SendMessage(RequestServerInfoMessage);
}

void UButtplugManager::RequestDeviceList()
{
	if (!WebSocket->IsConnected()) return;
	
	URequestDeviceListMessage *RequestDeviceListMessage = NewObject<URequestDeviceListMessage>();

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
	
	UStopAllDevicesMessage *StopAllDevicesMessage = NewObject<UStopAllDevicesMessage>();

	SendMessage(StopAllDevicesMessage);
}

void UButtplugManager::StopDeviceCmd(const int32 DeviceIndex) const
{
	if (!WebSocket->IsConnected()) return;
	
	UStopDeviceCmdMessage *StopDeviceCmdMessage = NewObject<UStopDeviceCmdMessage>();
	StopDeviceCmdMessage->DeviceIndex = DeviceIndex;

	SendMessage(StopDeviceCmdMessage);
}

void UButtplugManager::ScalarCmd(const int32 DeviceIndex, const TArray<FButtplugScalar> Scalars) const
{
	if (!WebSocket->IsConnected()) return;
	
	UScalarCmdMessage *ScalarCmdMessage = NewObject<UScalarCmdMessage>();
	ScalarCmdMessage->DeviceIndex = DeviceIndex;
	ScalarCmdMessage->Scalars = Scalars;

	SendMessage(ScalarCmdMessage);
}

void UButtplugManager::VibrateCmd(const int32 DeviceIndex, const TArray<FButtplugSpeed> Speeds) const
{
	if (!WebSocket->IsConnected()) return;

	UVibrateCmdMessage *VibrateCmdMessage = NewObject<UVibrateCmdMessage>();
	VibrateCmdMessage->DeviceIndex = DeviceIndex;
	VibrateCmdMessage->Speeds = Speeds;

	SendMessage(VibrateCmdMessage);
}

void UButtplugManager::LinearCmd(const int32 DeviceIndex, const TArray<FButtplugVector> Vectors) const
{
	if (!WebSocket->IsConnected()) return;

	ULinearCmdMessage *LinearCmdMessage = NewObject<ULinearCmdMessage>();
	LinearCmdMessage->DeviceIndex = DeviceIndex;
	LinearCmdMessage->Vectors = Vectors;

	SendMessage(LinearCmdMessage);
}

void UButtplugManager::RotateCmd(int32 DeviceIndex, TArray<FButtplugRotation> Rotations) const
{
	if (!WebSocket->IsConnected()) return;

	URotateCmdMessage *RotateCmdMessage = NewObject<URotateCmdMessage>();
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
	const FString MessageName = UButtplugMessage::GetMessageNameFromString(Message);

	if (MessageName == "ServerInfo")
	{
		UServerInfoMessage *ServerInfoMessage = NewObject<UServerInfoMessage>();
		ServerInfoMessage->DeserializeFromString(Message);
		
		OnConnected();

		// Start Ping Timer
		GetOwner()->GetWorldTimerManager().SetTimer(PingTimerHandler, this, &UButtplugManager::Ping, ServerInfoMessage->MaxPingTime / 2, true);

		// Request device list
		RequestDeviceList();
	}
	else if (MessageName == "DeviceAdded")
	{
		UDeviceAddedMessage *DeviceAddedMessage = NewObject<UDeviceAddedMessage>();
		DeviceAddedMessage->DeserializeFromString(Message);

		Devices.Add(DeviceAddedMessage->Device);
		
		OnDeviceAdded(DeviceAddedMessage->Device);
		OnDevicesChanged();
	}
	else if (MessageName == "DeviceRemoved")
	{
		UDeviceRemovedMessage *DeviceRemovedMessage = NewObject<UDeviceRemovedMessage>();
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
		UDeviceListMessage *DeviceListMessage = NewObject<UDeviceListMessage>();
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
		UScanningFinishedMessage *ScanningFinishedMessage = NewObject<UScanningFinishedMessage>();
		ScanningFinishedMessage->DeserializeFromString(Message);

		OnScanningFinished();
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
