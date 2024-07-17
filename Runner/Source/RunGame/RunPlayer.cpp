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
	//�������ɱ����
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//���齨�������������
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camrea"));
	FollowCamera->SetupAttachment(CameraBoom);
	//���õ��۵ĸ߶�
	CameraBoom->SetRelativeLocation(FVector(0, 0, 88));
	//���õ��۵ĳ���
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

	//������ӳ���������
	//��ȡ��ҿ�����
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController)
	{
		//��ȡ��ǿ������ϵͳ
		if(UEnhancedInputLocalPlayerSubsystem*InputSystem=PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMapping)
			{
				//������ӳ����ӵ���ϵͳ��
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
	//���������ϵͳת��Ϊ��ǿ����ϵͳ
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		if (MoveRightAction)
		{
			//ʹ����ǿ����ϵͳ�������������Ҫִ�еĺ������а󶨣�������������ʱ�����ݰ󶨵Ĺ�����к�������
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
		//��ȡ��������Z�ᣬ����������ǰ�ĵ�λ����
		FRotator YawRotation = FRotator(0, GetControlRotation().Yaw, 0);
		//ͨ���ṹ������ɫ��ǰ�ĵ�λ����
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection);
	}
}

void ARunPlayer::RunRight(const FInputActionValue& Value)
{
	float RightVlaue = Value.Get<float>();

	if (Controller && RightVlaue != 0 && !bIsCanTurn)
	{
		//��ȡ��������Z�ᣬ����������ǰ�ĵ�λ����
		FRotator YawRotation = FRotator(0, GetControlRotation().Yaw, 0);
		//ͨ���ṹ������ɫ��ǰ�ĵ�λ����
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
		//���Ž��ʰȡ��Ч
		UGameplayStatics::PlaySound2D(GetWorld(),CoinSound);
	}
}

int32 ARunPlayer::GetCoinTotalNum()
{
	return CoinNum;
}
