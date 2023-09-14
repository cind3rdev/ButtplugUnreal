// Copyright 2023 @Cinder. Licensed MIT.

#pragma once

#include "CoreMinimal.h"
#include "ButtplugManagerBase.h"
#include "ButtplugManager.generated.h"

/**
 * ButtplugManager extends ButtplugManagerBase with additional, higher level functionality
 * that is useful for most applications.
 */
UCLASS(Blueprintable)
class BUTTPLUGUNREAL_API UButtplugManager : public UButtplugManagerBase
{
	GENERATED_BODY()

private:
	void HandleConnected();
	
protected:
	UFUNCTION()
	virtual void BeginPlay() override;
	
public:	
	UPROPERTY(BlueprintReadWrite) bool ScanForDevicesOnConnected = true;
	
	UFUNCTION(BlueprintCallable) void VibrateForSeconds(int32 DeviceIndex, float TimeInSeconds, float Speed);
	UFUNCTION(BlueprintCallable) void TestDevice(int32 DeviceIndex);
};
