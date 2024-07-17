// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include"Components/BoxComponent.h"
#include"RunPlayer.h"
#include"../Classes/Kismet/GameplayStatics.h"
// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneRoot;

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MesnComponent"));
	CoinMesh->SetupAttachment(RootComponent);
	//将金币设置为无碰撞
	CoinMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentEndOverlap.AddDynamic(this, &ACoin::CoinBoxCallFun);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::CoinBoxCallFun(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ARunPlayer* RunPlayer = Cast<ARunPlayer>(OtherActor);
	if (RunPlayer)
	{
		RunPlayer->AddCoin();
		if (CoinSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), CoinSound);
		}
		Destroy();
	}
}

