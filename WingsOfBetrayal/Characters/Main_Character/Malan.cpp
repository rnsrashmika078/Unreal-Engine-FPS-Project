#include "WingsOfBetrayal/Characters/Main_Character/Malan.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "WingsOfBetrayal/Weapons/Weapon_Base.h"
#include "GameFramework/Actor.h"
#include "WingsOfBetrayal/Other/Bullet_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h" // this use for get world

AMalan::AMalan()
{
 
	PrimaryActorTick.bCanEverTick = true;


	////Attach Camera Booom to Character Mesh's Head Socket
	FPSSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FirstPerson Camera Boom"));
	FPSSpringArm->SetupAttachment(GetMesh(), TEXT("head"));
	FPSSpringArm->TargetArmLength = 0.f;
	FPSSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	FPSSpringArm->SetRelativeRotation(FRotator(-90.f, 90.f,0.f));//Red Blue Green  -> Pitch(X), Yaw(Z) , Roll(Y)

	

	////Attach Camera to Camera Boom
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS Camera"));
	FirstPersonCamera->SetupAttachment(FPSSpringArm);


	TPSSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPerson Camera Boom"));
	TPSSpringArm->TargetArmLength = 300.f;
	TPSSpringArm->SetupAttachment(RootComponent);

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS Camera"));
	ThirdPersonCamera->SetupAttachment(RootComponent);
	ThirdPersonCamera->SetupAttachment(TPSSpringArm);


	SubMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sub-Mesh"));
	SubMesh->SetupAttachment(RootComponent);

	isShooting = false;
	isAimDownSight = false;
	
	

}
void AMalan::BeginPlay()
{
	Super::BeginPlay();
	TempWeaponSpawner();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{

		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputsActionMappingContext, 0);
		}

		APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
		if (CameraManager)
		{
			CameraManager->ViewPitchMax = 40.f;
			CameraManager->ViewPitchMin = -40.f;
		}
	}

}
void AMalan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AMalan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMalan::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMalan::Look);
		//Shoot and ADS
	    EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AMalan::Shoot);
		EnhancedInputComponent->BindAction(AimDownSightAction, ETriggerEvent::Started, this, &AMalan::ToggleAimDownSight);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Started, this, &AMalan::StartWalk);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Completed, this, &AMalan::StopWalk);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMalan::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMalan::StopSprint);
	}
}
void AMalan::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}
void AMalan::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{ 
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
void AMalan::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("Firing")));

	if (!isShooting)
	{
		isShooting = true;
		if (SpawnedActor) //Check whether the character equipped with a weapon
		{
			USkeletalMeshComponent* WeaponMesh = SpawnedActor->WeaponMesh;
			if (WeaponMesh) 
			{
				FVector SpawnLocation = WeaponMesh->GetSocketLocation(FName(TEXT("bulletsocket")));
				FRotator SpawnRotation = WeaponMesh->GetSocketRotation(FName(TEXT("bulletsocket")));
				if (BulletActor) 
				{
					Bullet = GetWorld()->SpawnActor<ABullet_Base>(BulletActor, SpawnLocation, SpawnRotation);
					if (Bullet)
					{
						UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
						FIRE_ADS = SpawnedActor->WeaponStruct.FireMontages_ADS;
						FIRE_NO_ADS = SpawnedActor->WeaponStruct.FireMontages_Idle;
						if(AnimInstance && FIRE_NO_ADS && FIRE_ADS)
						{
							UAnimInstance* WeaponAnimInstance = WeaponMesh->GetAnimInstance();
							if (isAimDownSight) 
							{
								if (!AnimInstance->Montage_IsPlaying(FIRE_ADS)) 
								{
									AnimInstance->Montage_Play(FIRE_ADS);
									FOnMontageEnded EndDelegate;
									EndDelegate.BindUObject(this, &AMalan::OnMontageEnded);
									AnimInstance->Montage_SetEndDelegate(EndDelegate, FIRE_ADS);
									WeaponFireMontage = SpawnedActor->WeaponStruct.Weapon_Fire_Montage;
									if(WeaponAnimInstance && WeaponFireMontage)
									{
										WeaponAnimInstance->Montage_Play(WeaponFireMontage);
									}

								}
							}
							else 
							{
								if (!AnimInstance->Montage_IsPlaying(FIRE_NO_ADS))
								{
									AnimInstance->Montage_Play(FIRE_NO_ADS);
									FOnMontageEnded EndDelegate;
									EndDelegate.BindUObject(this, &AMalan::OnMontageEnded);
									AnimInstance->Montage_SetEndDelegate(EndDelegate, FIRE_NO_ADS);

									WeaponFireMontage = SpawnedActor->WeaponStruct.Weapon_Fire_Montage;
									if (WeaponAnimInstance && WeaponFireMontage)
									{
										WeaponAnimInstance->Montage_Play(WeaponFireMontage);
									}
								}
							}
						}
						
					}
				}
				
			}
		}
	}
}
void AMalan::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (SpawnedActor)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("Montage End")));
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		//UAnimInstance* SubAnimInstance = SubMesh->GetAnimInstance();
		UAnimInstance* WeaponAnimInstance = SpawnedActor->WeaponMesh->GetAnimInstance();
		Reload_ADS = SpawnedActor->WeaponStruct.ReloadMontage_ADS;
		Reload_NO_ADS = SpawnedActor->WeaponStruct.ReloadMontage_NO_ADS;
		WeaponReloadMontage = SpawnedActor->WeaponStruct.Weapon_Reload_Montage;
		switch (SpawnedActor->WeaponStruct.WeaponType)
		{
			case EWeaponType::SniperRifle:
				
				if (AnimInstance && Reload_ADS && !(Reload_NO_ADS) && WeaponReloadMontage)
				{
					if (isAimDownSight) 
					{
						AnimInstance->Montage_Play(Reload_ADS); // this should only play on left hand
						GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("Hide Bones Succeced!")));
							//SubAnimInstance->Montage_Play(Reload_ADS); // This will play on sub mesh ( hand mesh ) s' Right Hand
							FOnMontageEnded EndDelegate;
							EndDelegate.BindUObject(this, &AMalan::OnMontageEnded1);
							AnimInstance->Montage_SetEndDelegate(EndDelegate, Reload_ADS);
							WeaponAnimInstance->Montage_Play(WeaponReloadMontage);
						//if(SubAnimInstance)
						//{
						//	HideBones(true);
						//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("Hide Bones Succeced!")));
						//	//SubAnimInstance->Montage_Play(Reload_ADS); // This will play on sub mesh ( hand mesh ) s' Right Hand
						//	FOnMontageEnded EndDelegate;
						//	EndDelegate.BindUObject(this, &AMalan::OnMontageEnded1);
						//	AnimInstance->Montage_SetEndDelegate(EndDelegate, Reload_ADS);
						//	WeaponAnimInstance->Montage_Play(WeaponReloadMontage);
						//}
						
					}
					else 
					{

						AnimInstance->Montage_Play(Reload_NO_ADS);
						FOnMontageEnded EndDelegate;
						EndDelegate.BindUObject(this, &AMalan::OnMontageEnded1);
						AnimInstance->Montage_SetEndDelegate(EndDelegate, Reload_NO_ADS);
						WeaponAnimInstance->Montage_Play(WeaponReloadMontage);
					}

				}
				break;
			default:
				break;
		}
		isShooting = false;
	}
}
void AMalan::OnMontageEnded1(UAnimMontage* Montage, bool bInterrupted)
{
	//if (isAimDownSight)
	//{
	//	HideBones(false);
	//	isShooting = false;
	//}
	//else 
	//{
	//	isShooting = false;
	//}
	isShooting = false;
	
}
void AMalan::ToggleAimDownSight() 
{
	if (!isAimDownSight)
	{
		AimDownSightON();
	}
	else
	{
		AimDownSightOFF();
	}
}

void AMalan::AimDownSightON()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("This is Triggering")));
	/*if(SpawnedActor)
	{
		
	}*/
	isAimDownSight = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

}
void AMalan::AimDownSightOFF() 
{
	/*if (SpawnedActor) 
	{
	}*/
	isAimDownSight = false;
	GetCharacterMovement()->MaxWalkSpeed = 900.f;

}
FRotator AMalan::SpineRotation() 
{
	FRotator ControlRotation = GetControlRotation();
	FRotator ActorRotation = GetActorRotation();
	FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(ControlRotation, ActorRotation);

	float Yaw = DeltaRotation.Yaw;
	float Pitch = DeltaRotation.Pitch * -1;
	float Roll = 0.f;

	//float ClampedYaw = FMath::Clamp(Yaw, -90.f, 90.f);   
	//float ClampedPitch = FMath::Clamp(Pitch, -20.f, 20.f); 

	FRotator NewAimOffset = FRotator(Pitch, Yaw, Roll);
	return NewAimOffset;

}
void AMalan::TempWeaponSpawner() 
{
	FVector SpawnLocation = FVector(0.f, 0.f, 0.f);
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	if(ActorToSpawn)
	{
		SpawnedActor = GetWorld()->SpawnActor<AWeapon_Base>(ActorToSpawn, SpawnLocation, SpawnRotation);
		if (SpawnedActor) 
		{
			FName Socket = SpawnedActor->WeaponStruct.SocketName;
			SpawnedActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(Socket));
		}
	}
}
void AMalan::HideBones(bool hide)
{
	if (hide)
	{
		SubMesh->HideBoneByName(FName(TEXT("clavicle_l")), EPhysBodyOp::PBO_None);
		GetMesh()->HideBoneByName(FName(TEXT("clavicle_r")), EPhysBodyOp::PBO_None);
	}
	else
	{
		SubMesh->UnHideBoneByName(FName(TEXT("clavicle_l")));
		GetMesh()->UnHideBoneByName(FName(TEXT("clavicle_r")));
	}
	
}
void AMalan::StartWalk()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Walking")));
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}
void AMalan::StopWalk()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Not Walking")));
	GetCharacterMovement()->MaxWalkSpeed = 900.f;
}
void AMalan::StartSprint() 
{
	GetCharacterMovement()->MaxWalkSpeed = 1200.f;
	isAimDownSight = false;
}
void AMalan::StopSprint() 
{
	GetCharacterMovement()->MaxWalkSpeed = 900.f;
	isAimDownSight = false;

}
void AMalan::ActivateCameraLag(bool bCameraLagActivate, bool bCameraRotationLagActivate, float FPSCameraLagSpeed, float FPSCameraRotationLag, float FPSCameraLagMaxDistance)
{
	FPSSpringArm->bEnableCameraLag = bCameraLagActivate;
	FPSSpringArm->bEnableCameraRotationLag = bCameraRotationLagActivate;
	FPSSpringArm->CameraLagSpeed = FPSCameraLagSpeed;
	FPSSpringArm->CameraRotationLagSpeed = FPSCameraRotationLag;
	FPSSpringArm->CameraLagMaxDistance = FPSCameraLagMaxDistance;
}
