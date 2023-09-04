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
	
	void BindWebSocketEvents();
	void SendMessage(UButtplugMessage* Message) const;
	void Ping() const;
	void HandleIncomingMessage(const FString& Message);
	static void EnsureModuleLoaded(const FString& ModuleName);
	
public:		
	UPROPERTY(BlueprintReadWrite) FString ClientName = TEXT("ButtplugUnreal");
	UPROPERTY(BlueprintReadWrite) FString ServerAddress = TEXT("ws://127.0.0.1:12345/");
	UPROPERTY(BlueprintReadOnly) TArray<FButtplugDevice> Devices = TArray<FButtplugDevice>();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable) void Connect();
	UFUNCTION(BlueprintCallable) void Shutdown();
	UFUNCTION(BlueprintCallable) bool IsConnected();

	UFUNCTION(BlueprintCallable) void StartScanning();
	UFUNCTION(BlueprintCallable) void StopScanning();
	UFUNCTION(BlueprintCallable) void RequestServerInfo();

	UFUNCTION(BlueprintCallable) void RequestDeviceList();
	UFUNCTION(BlueprintCallable) void StopAllDevices();
	UFUNCTION(BlueprintCallable) void StopDeviceCmd(int32 DeviceIndex) const;
	
	UFUNCTION(BlueprintCallable) void ScalarCmd(int32 DeviceIndex, TArray<FButtplugScalar> Scalars) const;
	UFUNCTION(BlueprintCallable) void VibrateCmd(int32 DeviceIndex, TArray<FButtplugSpeed> Speeds) const;
	UFUNCTION(BlueprintCallable) void LinearCmd(int32 DeviceIndex, TArray<FButtplugVector> Vectors) const;
	UFUNCTION(BlueprintCallable) void RotateCmd(int32 DeviceIndex, TArray<FButtplugRotation> Rotations) const;

	UFUNCTION(BlueprintCallable) void BasicVibrate(int32 DeviceIndex, float Speed) const;

	UFUNCTION(BlueprintImplementableEvent) void OnConnected();
	UFUNCTION(BlueprintImplementableEvent) void OnDisconnected(int32 StatusCode, const FString& Reason, bool WasClean);
	UFUNCTION(BlueprintImplementableEvent) void OnDeviceAdded(FButtplugDevice Device);
	UFUNCTION(BlueprintImplementableEvent) void OnDeviceRemoved(int32 DeviceIndex);
	UFUNCTION(BlueprintImplementableEvent) void OnDevicesChanged();
	UFUNCTION(BlueprintImplementableEvent) void OnScanningFinished();
	UFUNCTION(BlueprintImplementableEvent) void OnError(const FString& Message);
};
