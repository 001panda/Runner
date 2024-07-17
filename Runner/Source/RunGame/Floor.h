// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor.generated.h"

UCLASS()
class RUNGAME_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTransform GetNextFloorTransform();
	
	UFUNCTION()
	void PassBoxCallFun(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	void TurnBoxCallFun(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	void SpawnCoinOnFloor();

protected:
	//作为根组件使用
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class USceneComponent* RootScene;

	//用来存放地板模型组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* FloorMesh;

	//检测框，1、检测玩家是否通过这块地板
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Pass_DetectionBox;

	//检测框，2、检测玩家是否能够拐弯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Turn_DetectionBox;

	//箭头组件：1、标识下一块地板生成位置
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* SpawnArrow_NextFloor;
	//箭头组件：2、标识金币生成方向
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* SpawnArrow_CoinA;
	//箭头组件：3、标识金币生成方向
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* SpawnArrow_CoinB;
	//箭头组件：4、标识金币生成方向
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* SpawnArrow_CoinC;

	//地板上的金币
	TArray<class ACoin*> FloorCoinArray;
};
