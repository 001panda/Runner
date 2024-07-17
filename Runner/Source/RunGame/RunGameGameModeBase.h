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
	//�����ȡ�ذ���
	UClass* RandomFloorClass(EFloorType FloorType=EFloorType::All,float RandomTurnRate=0.2f);
	//��������ĵذ�
	void SpawnRandomFloor(UClass* FloorClass);

	//�������ǵĺ���
	TArray<class ACoin*> RandomSpawnCoin(class UArrowComponent* SpawnDirection, int32 SpawnNum = 15, float Interval = 120);
	

protected:
	//�洢ֱ�ذ����Դ
	TArray<UClass*>StraightFloorArray;
	//�洢ת��ذ����Դ
	TArray<UClass*>TurnFloorArray;
	//��ǰ�ذ����ɵ�λ��
	FTransform CurrentFloorLocation;

	TSubclassOf<class ACoin> CoinClass;
};
