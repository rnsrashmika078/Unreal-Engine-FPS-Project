// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FPSPlayer.generated.h"

UCLASS()
class WINGSOFBETRAYAL_API AFPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//SpringArm Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent* FPSSpringArm;

	//SpringArm Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent* TPSSpringArm;

	//Camera Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* FirstPersonCamera;

	//Camera Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* ThirdPersonCamera;

	//Enhanced Input 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputMappingContext")
	class UInputMappingContext* InputsActionMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	class UInputAction* LookAction;


	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

};
