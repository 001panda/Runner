// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RunPlayer.generated.h"

UCLASS()
class RUNGAME_API ARunPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	//声明弹簧组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;
	//声明相机组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;


public:
	//向前移动
	void RunForward();
	//左右移动函数
	void RunRight(const FInputActionValue&Value);

	//左右拐弯
	void RunTurn(const FInputActionValue& Value);

	void SetCanTurn();

	//拾取金币调用的函数

	void AddCoin();

	//获取金币数量
	int32 GetCoinTotalNum();
protected:
	bool bIsRun = true;
	bool bIsCanTurn = false;

protected:
	//声明输入操作，操作映射的执行函数
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	//声明输入映射，在C++中启动
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMapping;

	//拾取金币数量
	int32 CoinNum;

	class USoundBase* CoinSound;
};
