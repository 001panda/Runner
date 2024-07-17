// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "RunPlayer.h"
#include "RunGameGameModeBase.h"
#include "Coin.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建根场景组件
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = RootScene;

	FloorMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	FloorMesh->SetupAttachment(RootComponent);

	Pass_DetectionBox= CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBoxPass"));
	Pass_DetectionBox->SetupAttachment(RootComponent);

	Turn_DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBoxTurn"));
	Turn_DetectionBox->SetupAttachment(RootComponent);

	SpawnArrow_NextFloor= CreateDefaultSubobject<UArrowComponent>(TEXT("NextFloorArrow"));
	SpawnArrow_NextFloor->SetupAttachment(RootComponent);

	SpawnArrow_CoinA = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrow_CoinA"));
	SpawnArrow_CoinA->SetupAttachment(RootComponent);

	SpawnArrow_CoinB = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrow_CoinB"));
	SpawnArrow_CoinB->SetupAttachment(RootComponent);

	SpawnArrow_CoinC = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrow_CoinC"));
	SpawnArrow_CoinC->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	Pass_DetectionBox->OnComponentEndOverlap.AddDynamic(this, &AFloor::PassBoxCallFun);
	Turn_DetectionBox->OnComponentEndOverlap.AddDynamic(this, &AFloor::TurnBoxCallFun);

	SpawnCoinOnFloor();
}
//销毁金币和地板
void AFloor::Destroyed()
{
	for (ACoin* Coin : FloorCoinArray)
	{
		Coin->Destroy();
		Coin = nullptr;
	}
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FTransform AFloor::GetNextFloorTransform()
{
	FTransform NextFloorTransform;
	NextFloorTransform.SetLocation(SpawnArrow_NextFloor->GetComponentToWorld().GetLocation());
	NextFloorTransform.SetRotation(SpawnArrow_NextFloor->GetComponentToWorld().GetRotation());
	return NextFloorTransform;
}

void AFloor::PassBoxCallFun(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ARunPlayer* RunPlayer = Cast<ARunPlayer>(OtherActor);
	if (RunPlayer)
	{
		//设置当地板的生命时长
		this->SetLifeSpan(3.0f);
		//生成下一块地板
		ARunGameGameModeBase* GM = GetWorld()->GetAuthGameMode<ARunGameGameModeBase>();
		if (GM)
		{
			GM->SpawnRandomFloor(GM->RandomFloorClass(EFloorType::All,0.5f));
		}
	}


}

void AFloor::TurnBoxCallFun(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ARunPlayer* RunPlayer = Cast<ARunPlayer>(OtherActor);
	if (RunPlayer)
	{
		RunPlayer->SetCanTurn();
		
	}
}

void AFloor::SpawnCoinOnFloor()
{
	ARunGameGameModeBase* RunGameMode = Cast<ARunGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (RunGameMode)
	{
		int32 DirectionIndex = FMath::RandRange(1, 3);
		int32 SpawnName = FMath::RandRange(5,15);
		switch (DirectionIndex)
		{
		case 1:
			FloorCoinArray = RunGameMode->RandomSpawnCoin(SpawnArrow_CoinA, SpawnName);
			break;
		case 2:
			FloorCoinArray = RunGameMode->RandomSpawnCoin(SpawnArrow_CoinB, SpawnName);

			break;
		case 3:
			FloorCoinArray = RunGameMode->RandomSpawnCoin(SpawnArrow_CoinC, SpawnName);

			break;
		default:
			break;
		}
	}
}

