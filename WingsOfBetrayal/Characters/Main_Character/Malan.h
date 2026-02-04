// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Malan.generated.h"


UCLASS()
class WINGSOFBETRAYAL_API AMalan : public ACharacter
{
	GENERATED_BODY()

public:
	AMalan();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//SpringArm Component
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USpringArmComponent* FPSSpringArm;

	//SpringArm Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent* TPSSpringArm;

	//Camera Component
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UCameraComponent* FirstPersonCamera;

	//Camera Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* ThirdPersonCamera;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USkeletalMeshComponent* SubMesh;

	

	//Enhanced Input 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputMappingContext")
	class UInputMappingContext* InputsActionMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	class UInputAction* LookAction;

	//Shoot and Aim Down Sight
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	class UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	class UInputAction* AimDownSightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
	class UInputAction* WalkAction;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool isShooting;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isAimDownSight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isWalking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isRunning;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isSprinting;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AWeapon_Base> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class ABullet_Base> BulletActor;

	UPROPERTY(BlueprintReadOnly)
	AWeapon_Base* SpawnedActor;
	UPROPERTY(BlueprintReadOnly)
	ABullet_Base* Bullet;

	

	//Move and Look Function Related to Enhanced Input System
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	//Spine Rotation ( Aim Offset )
	FRotator SpineRotation();

	//Shoot and Aim Down Sight Functions
	void Shoot();
	void AimDownSightON();
	void AimDownSightOFF();
	void ToggleAimDownSight();
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnMontageEnded1(UAnimMontage* Montage, bool bInterrupted);
	//Temp Functions
	void TempWeaponSpawner();

	/*void LimitCameraRotation();*/

	//Hide Bone by name
	void HideBones(bool hide);

	void StartWalk();
	void StopWalk();
	void StartSprint();
	void StopSprint();
	void ActivateCameraLag(bool bCameraLagActivate,bool bCameraRotationLagActivate,float FPSCameraLagSpeed,float FPSCameraRotationLag,float FPSCameraLagMaxDistance);
	//Montages
	UAnimMontage* FIRE_NO_ADS;
	UAnimMontage* FIRE_ADS;
	UAnimMontage* WeaponFireMontage;
	UAnimMontage* Reload_NO_ADS;
	UAnimMontage* Reload_ADS;
	UAnimMontage* WeaponReloadMontage;

	
};
