// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameGameModeBase.generated.h"


UENUM(BlueprintType)
enum class EFloorType:uint8
{
	All,
	StraightFloor,
	TurnFloor
};

/**
 * 
 */
UCLASS()
class RUNGAME_API ARunGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	ARunGameGameModeBase();


protected:
	virtual void BeginPlay() override;
public:
	//随机获取地板类
	UClass* RandomFloorClass(EFloorType FloorType=EFloorType::All,float RandomTurnRate=0.2f);
	//生成随机的地板
	void SpawnRandomFloor(UClass* FloorClass);

	//生成星星的函数
	TArray<class ACoin*> RandomSpawnCoin(class UArrowComponent* SpawnDirection, int32 SpawnNum = 15, float Interval = 120);
	

protected:
	//存储直地板的资源
	TArray<UClass*>StraightFloorArray;
	//存储转弯地板的资源
	TArray<UClass*>TurnFloorArray;
	//当前地板生成的位置
	FTransform CurrentFloorLocation;

	TSubclassOf<class ACoin> CoinClass;
};
