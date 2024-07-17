// Copyright Epic Games, Inc. All Rights Reserved.


#include "RunGameGameModeBase.h"
#include"RunPlayer.h"
#include "Floor.h"
#include "Coin.h"
#include "Components/ArrowComponent.h"
ARunGameGameModeBase::ARunGameGameModeBase()
{
	//ͨ�������������Դ����ͼ����Դ��Ҫ����Դ���ú����-c
	ConstructorHelpers::FClassFinder<ARunPlayer>PlayerClass(TEXT("/Script/Engine.Blueprint'/Game/RunGmae/BluePrints/Player/BP_Player.BP_Player_C'"));
	//����Ĭ�Ͻ�ɫ
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
	//�������10��ֱ�ذ�
	for (int32 i = 0; i < 5; i++)
	{
		SpawnRandomFloor(RandomFloorClass(EFloorType::StraightFloor));
	}
}

UClass* ARunGameGameModeBase::RandomFloorClass(EFloorType FloorType, float RandomTurnRate)
{
	//���һ��0��1��ֵ
	float RandomValue = FMath::RandRange(0.0f, 1.0f);
	int32 TurnIndex;
	int32 StraightIndex;
	switch (FloorType)
	{
	case EFloorType::All:
		//�����ж����ɹ���廹��ֱ�ذ�
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
			//��ȡ������ɷ���
			FVector CoinSpawnDirection = FRotationMatrix(FRotator(SpawnDirection->GetComponentToWorld().GetRotation())).GetUnitAxis(EAxis::X);
			//����������λ��
			FVector CoinLocation = SpawnDirection->GetComponentToWorld().GetLocation() + CoinSpawnDirection * i * Interval + FVector(0,0,SpawnHigh);
			//���ɽ��
			ACoin* CoinInstance = GetWorld()->SpawnActor<ACoin>(CoinClass, CoinLocation, FRotator::ZeroRotator);
			CoinArray.Add(CoinInstance);

		}
	}
	return CoinArray;
}



