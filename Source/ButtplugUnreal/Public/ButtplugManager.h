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
#include "ButtplugManager.generated.h"

/**
 * ButtplugManager is the main class for interacting with Buttplug. It handles
 * connecting to the server, sending and receiving messages, and maintaining a
 * connected devices list.
 */
UCLASS(Blueprintable)
class BUTTPLUGUNREAL_API UButtplugManager : public UActorComponent
{
	GENERATED_BODY()

	TSharedPtr<IWebSocket> WebSocket;
	FTimerHandle PingTimerHandler;
	
	void OnWebSocketClosed(int32 StatusCode, const FString& Reason, bool WasClean);
	void Ping();
	void OnWebSocketConnected();
	void OnWebSocketConnectionError(const FString& Error);
	void OnWebSocketMessage(const FString& Message);
	static void EnsureModuleLoaded(const FString& ModuleName);
	
public:		
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

	UFUNCTION(BlueprintImplementableEvent) void OnConnected();
	UFUNCTION(BlueprintImplementableEvent) void OnDisconnected(int32 StatusCode, const FString& Reason, bool WasClean);
	UFUNCTION(BlueprintImplementableEvent) void OnError(const FString& Message);
	UFUNCTION(BlueprintImplementableEvent) void OnWebSocketError(const FString& Message);
	
	UFUNCTION(BlueprintImplementableEvent) void OnDeviceAdded(FButtplugDevice Device);
	UFUNCTION(BlueprintImplementableEvent) void OnDeviceRemoved(int32 DeviceIndex);
	UFUNCTION(BlueprintImplementableEvent) void OnDevicesChanged();
	UFUNCTION(BlueprintImplementableEvent) void OnScanningFinished();

	UFUNCTION(BlueprintImplementableEvent) void OnSensorReading(USensorReadingMessage* SensorReadingMessage);

	UFUNCTION(BlueprintImplementableEvent) void OnButtplugError(UErrorMessage* ErrorMessage);
};
