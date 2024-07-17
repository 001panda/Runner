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
	//��Ϊ�����ʹ��
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class USceneComponent* RootScene;

	//������ŵذ�ģ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* FloorMesh;

	//����1���������Ƿ�ͨ�����ذ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Pass_DetectionBox;

	//����2���������Ƿ��ܹ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Turn_DetectionBox;

	//��ͷ�����1����ʶ��һ��ذ�����λ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* SpawnArrow_NextFloor;
	//��ͷ�����2����ʶ������ɷ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* SpawnArrow_CoinA;
	//��ͷ�����3����ʶ������ɷ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* SpawnArrow_CoinB;
	//��ͷ�����4����ʶ������ɷ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* SpawnArrow_CoinC;

	//�ذ��ϵĽ��
	TArray<class ACoin*> FloorCoinArray;
};
