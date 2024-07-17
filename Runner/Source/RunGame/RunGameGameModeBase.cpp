// Copyright Epic Games, Inc. All Rights Reserved.


#include "RunGameGameModeBase.h"
#include"RunPlayer.h"
#include "Floor.h"
#include "Coin.h"
#include "Components/ArrowComponent.h"
ARunGameGameModeBase::ARunGameGameModeBase()
{
	//通过构造加载类资源，蓝图类资源需要早资源引用后面加-c
	ConstructorHelpers::FClassFinder<ARunPlayer>PlayerClass(TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Player/BP_Player.BP_Player_C'"));
	//设置默认角色
	DefaultPawnClass = PlayerClass.Class;

	UClass*FloorClass=LoadClass<AFloor>(NULL, TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Floor/BP_Floor1.BP_Floor1_C'"));
	StraightFloorArray.AddUnique(FloorClass);

	FloorClass = LoadClass<AFloor>(NULL, TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Floor/BP_Floor2.BP_Floor2_C'"));
	StraightFloorArray.AddUnique(FloorClass);



	FloorClass = LoadClass<AFloor>(NULL, TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Floor/BP_Floor3.BP_Floor3_C'"));
	StraightFloorArray.AddUnique(FloorClass);

	FloorClass = LoadClass<AFloor>(NULL, TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Floor/BP_Floor4.BP_Floor4_C'"));
	StraightFloorArray.AddUnique(FloorClass);


	FloorClass = LoadClass<AFloor>(NULL, TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Floor/BP_Floor5.BP_Floor5_C'"));
	StraightFloorArray.AddUnique(FloorClass);

	FloorClass = LoadClass<AFloor>(NULL, TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Floor/BP_Floor6.BP_Floor6_C'"));
	StraightFloorArray.AddUnique(FloorClass);

	FloorClass = LoadClass<AFloor>(NULL, TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Floor/BP_Floor7.BP_Floor7_C'"));
	TurnFloorArray.AddUnique(FloorClass);

	FloorClass = LoadClass<AFloor>(NULL, TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Floor/BP_Floor8.BP_Floor8_C'"));
	TurnFloorArray.AddUnique(FloorClass);

	CoinClass = LoadClass<ACoin>(NULL, TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Coin/BP_Coin.BP_Coin_C'"));
}

void ARunGameGameModeBase::BeginPlay()
{
	//随机生成10个直地板
	for (int32 i = 0; i < 5; i++)
	{
		SpawnRandomFloor(RandomFloorClass(EFloorType::StraightFloor));
	}
}

UClass* ARunGameGameModeBase::RandomFloorClass(EFloorType FloorType, float RandomTurnRate)
{
	//随机一个0到1的值
	float RandomValue = FMath::RandRange(0.0f, 1.0f);
	int32 TurnIndex;
	int32 StraightIndex;
	switch (FloorType)
	{
	case EFloorType::All:
		//用来判定生成拐弯板还是直地板
		if (RandomValue<= RandomTurnRate)
		{
			 TurnIndex = FMath::RandRange(0, TurnFloorArray.Num() - 1);
			return TurnFloorArray[TurnIndex];
		}
		else
		{
			 StraightIndex = FMath::RandRange(0, StraightFloorArray.Num() - 1);
			return StraightFloorArray[StraightIndex];
		}
		break;
	case EFloorType::StraightFloor:
		 StraightIndex = FMath::RandRange(0, StraightFloorArray.Num() - 1);
		return StraightFloorArray[StraightIndex];
		break;
	case EFloorType::TurnFloor:
		 TurnIndex = FMath::RandRange(0, TurnFloorArray.Num() - 1);
		return TurnFloorArray[TurnIndex];
		break;
	}
	return nullptr;
}

void ARunGameGameModeBase::SpawnRandomFloor(UClass* FloorClass)
{
	if (FloorClass)
	{
		AFloor* FloorSpawned = GetWorld()->SpawnActor<AFloor>(FloorClass, CurrentFloorLocation);

		CurrentFloorLocation = FloorSpawned->GetNextFloorTransform();

	}
}

TArray<class ACoin*> ARunGameGameModeBase::RandomSpawnCoin(UArrowComponent* SpawnDirection, int32 SpawnNum, float Interval)
{
	TArray<ACoin*> CoinArray;
	float SpawnHigh = FMath::RandRange(-50.0f, 50.0f);
	if (SpawnDirection && SpawnNum > 0 && Interval > 50)
	{
		for (int32 i = 0; i < SpawnNum; i++)
		{
			if (CoinClass==nullptr)
			{
				break;
			}
			//获取金币生成方向
			FVector CoinSpawnDirection = FRotationMatrix(FRotator(SpawnDirection->GetComponentToWorld().GetRotation())).GetUnitAxis(EAxis::X);
			//计算金币生成位置
			FVector CoinLocation = SpawnDirection->GetComponentToWorld().GetLocation() + CoinSpawnDirection * i * Interval + FVector(0,0,SpawnHigh);
			//生成金币
			ACoin* CoinInstance = GetWorld()->SpawnActor<ACoin>(CoinClass, CoinLocation, FRotator::ZeroRotator);
			CoinArray.Add(CoinInstance);

		}
	}
	return CoinArray;
}



