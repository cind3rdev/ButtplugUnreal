// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugRotation.h"
#include "IWebSocket.h"
#include "ButtplugScalar.h"
#include "ButtplugSpeed.h"
#include "ButtplugVector.h"
#include "Messages/ButtplugMessage.h"
#include "Messages/DeviceAddedMessage.h"
#include "Messages/ErrorMessage.h"
#include "Messages/SensorReadingMessage.h"
#include "ButtplugManagerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDisconnected, int32, StatusCode, const FString&, Reason, bool, WasClean);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FError, const FString&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketError, const FString&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtplugError, UErrorMessage*, Message);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDevicesUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceAdded, FButtplugDevice, Device);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceRemoved, int32, DeviceIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScanningFinished);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSensorReading, USensorReadingMessage*, SensorReadingMessage);

/**
 * ButtplugManagerBase is the main class for interacting with Buttplug. It handles
 * connecting to the server, sending and receiving messages, and maintaining a
 * connected devices list.
 */
UCLASS(Blueprintable)
class BUTTPLUGUNREAL_API UButtplugManagerBase : public UActorComponent
{
	GENERATED_BODY()

	TSharedPtr<IWebSocket> WebSocket;
	FTimerHandle PingTimerHandler;
	
	void Ping();

	UFUNCTION() void OnWebSocketConnected();
	UFUNCTION() void OnWebSocketConnectionError(const FString& Error);
	UFUNCTION() void OnWebSocketMessage(const FString& Message);
	UFUNCTION() void OnWebSocketClosed(int32 StatusCode, const FString& Reason, bool WasClean);
	
	static void EnsureModuleLoaded(const FString& ModuleName);
	
public:
	UPROPERTY(BlueprintAssignable) FConnected OnConnected;
	UPROPERTY(BlueprintAssignable) FDisconnected OnDisconnected;
	UPROPERTY(BlueprintAssignable) FError OnError;
	UPROPERTY(BlueprintAssignable) FWebSocketError OnWebSocketError;
	UPROPERTY(BlueprintAssignable) FButtplugError OnButtplugError;

	UPROPERTY(BlueprintAssignable) FDevicesUpdated OnDevicesUpdated;
	UPROPERTY(BlueprintAssignable) FDeviceAdded OnDeviceAdded;
	UPROPERTY(BlueprintAssignable) FDeviceRemoved OnDeviceRemoved;
	UPROPERTY(BlueprintAssignable) FScanningFinished OnScanningFinished;

	UPROPERTY(BlueprintAssignable) FSensorReading OnSensorReading;
	
	UPROPERTY(BlueprintReadWrite) FString ClientName = TEXT("ButtplugUnreal");
	UPROPERTY(BlueprintReadWrite) FString ServerAddress = TEXT("ws://127.0.0.1:12345/");
	UPROPERTY(BlueprintReadOnly) TArray<FButtplugDevice> Devices = TArray<FButtplugDevice>();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable) void Connect();
	UFUNCTION(BlueprintCallable) void Shutdown();
	UFUNCTION(BlueprintCallable) bool IsConnected();

	UFUNCTION(BlueprintCallable) void SendMessage(UButtplugMessage* Message);

	UFUNCTION(BlueprintCallable) void StartScanning();
	UFUNCTION(BlueprintCallable) void StopScanning();
	UFUNCTION(BlueprintCallable) void RequestServerInfo();

	UFUNCTION(BlueprintCallable) void RequestDeviceList();
	UFUNCTION(BlueprintCallable) void StopAllDevices();
	UFUNCTION(BlueprintCallable) void StopDeviceCmd(int32 DeviceIndex);

	UFUNCTION(BlueprintCallable) void SensorReadCmd(int32 DeviceIndex, int32 SensorIndex, FString SensorType);
	UFUNCTION(BlueprintCallable) void SensorSubscribeCmd(int32 DeviceIndex, int32 SensorIndex, FString SensorType);
	UFUNCTION(BlueprintCallable) void SensorUnsubscribeCmd(int32 DeviceIndex, int32 SensorIndex, FString SensorType);
	
	UFUNCTION(BlueprintCallable) void ScalarCmd(int32 DeviceIndex, TArray<FButtplugScalar> Scalars);
	UFUNCTION(BlueprintCallable) void VibrateCmd(int32 DeviceIndex, TArray<FButtplugSpeed> Speeds);
	UFUNCTION(BlueprintCallable) void LinearCmd(int32 DeviceIndex, TArray<FButtplugVector> Vectors);
	UFUNCTION(BlueprintCallable) void RotateCmd(int32 DeviceIndex, TArray<FButtplugRotation> Rotations);

	UFUNCTION(BlueprintCallable) void BasicVibrate(int32 DeviceIndex, float Speed);
};
