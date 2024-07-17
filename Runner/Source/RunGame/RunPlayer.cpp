// Fill out your copyright notice in the Description page of Project Settings.


#include "RunPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARunPlayer::ARunPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//创建弹簧臂组件
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//将组建依附到根组件下
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camrea"));
	FollowCamera->SetupAttachment(CameraBoom);
	//设置吊臂的高度
	CameraBoom->SetRelativeLocation(FVector(0, 0, 88));
	//设置吊臂的长度
	CameraBoom->TargetArmLength = 800.0f;

	CameraBoom->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ARunPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (Controller)
	{
		Controller->SetControlRotation(FRotator(-30.0, 0.0, 0.0));

	}

	//将输入映射进行启用
	//获取玩家控制器
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController)
	{
		//获取增强输入子系统
		if(UEnhancedInputLocalPlayerSubsystem*InputSystem=PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMapping)
			{
				//将输入映射添加到子系统中
				InputSystem->AddMappingContext(InputMapping,0);
			}
		}
	}
}

// Called every frame
void ARunPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunForward();
}

// Called to bind functionality to input
void ARunPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//将玩家输入系统转换为增强输入系统
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		if (MoveRightAction)
		{
			//使用增强输入系统，将输入操作和要执行的函数进行绑定，当操作被触发时，根据绑定的规则进行函数调用
			EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ARunPlayer::RunRight);
		}
		if (TurnAction)
		{
			EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &ARunPlayer::RunTurn);

		}
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARunPlayer::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARunPlayer::StopJumping);

		}
	}

}

void ARunPlayer::RunForward()
{
	if (bIsRun&&Controller)
	{
		//获取控制器的Z轴，用来计算向前的单位向量
		FRotator YawRotation = FRotator(0, GetControlRotation().Yaw, 0);
		//通过结构体计算角色向前的单位向量
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection);
	}
}

void ARunPlayer::RunRight(const FInputActionValue& Value)
{
	float RightVlaue = Value.Get<float>();

	if (Controller && RightVlaue != 0 && !bIsCanTurn)
	{
		//获取控制器的Z轴，用来计算向前的单位向量
		FRotator YawRotation = FRotator(0, GetControlRotation().Yaw, 0);
		//通过结构体计算角色向前的单位向量
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDirection, RightVlaue);
	}
}

void ARunPlayer::RunTurn(const FInputActionValue& Value)
{
	float TurnVlaue = Value.Get<float>();

	if (Controller && TurnVlaue != 0 && bIsCanTurn)
	{
		Controller->SetControlRotation(FRotator(GetControlRotation().Pitch, GetControlRotation().Yaw + TurnVlaue * 90, 0));
		bIsCanTurn = false;
	}
}

void ARunPlayer::SetCanTurn()
{
	this->bIsCanTurn = true;
}

void ARunPlayer::AddCoin()
{
	CoinNum++;
	if (CoinSound)
	{
		//播放金币拾取音效
		UGameplayStatics::PlaySound2D(GetWorld(),CoinSound);
	}
}

int32 ARunPlayer::GetCoinTotalNum()
{
	return CoinNum;
}
