// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class RUNGAME_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CoinMesh;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere,Category="Sound")
	class USoundBase* CoinSound;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CoinBoxCallFun(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
