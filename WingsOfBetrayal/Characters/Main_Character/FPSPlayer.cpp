// Fill out your copyright notice in the Description page of Project Settings.


#include "WingsOfBetrayal/Characters/Main_Character/FPSPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	////Attach Camera Booom to Character Mesh's Head Socket
	FPSSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FirstPerson Camera Boom"));
	FPSSpringArm->SetupAttachment(GetMesh(), TEXT("head"));
	FPSSpringArm->TargetArmLength = 0.f;
	FPSSpringArm->SetRelativeLocation(FVector(4.5f, 3.5f, 0.f));
	FPSSpringArm->SetRelativeRotation(FRotator(-90.f, 90.f, 0.f));//Red Blue Green  -> Pitch(X), Yaw(Z) , Roll(Y)

	////Attach Camera to Camera Boom
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS Camera"));
	FirstPersonCamera->SetupAttachment(FPSSpringArm);


	TPSSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPerson Camera Boom"));
	TPSSpringArm->TargetArmLength = 300.f;
	TPSSpringArm->SetupAttachment(RootComponent);

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS Camera"));
	ThirdPersonCamera->SetupAttachment(RootComponent);
	ThirdPersonCamera->SetupAttachment(TPSSpringArm);

}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputsActionMappingContext, 0);
		}
	}
	
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Look);

	}

}
void AFPSPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}