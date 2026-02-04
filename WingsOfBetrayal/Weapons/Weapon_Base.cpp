// Fill out your copyright notice in the Description page of Project Settings.


#include "WingsOfBetrayal/Weapons/Weapon_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "WingsOfBetrayal/Characters/Main_Character/Malan.h" 
//#include "Components/StaticMeshComponent.h"

// Sets default values
AWeapon_Base::AWeapon_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ScopeSensitivity = 0.3f;
	NormalSensitivity = 2.5f;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SphereCollider->SetupAttachment(RootComponent);
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(SphereCollider);

	Scope = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponScope"));
	Scope->SetupAttachment(SphereCollider);


	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCaptureComponent->SetupAttachment(SphereCollider);

	NonScope = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OtherScope"));
	NonScope->SetupAttachment(SphereCollider);

	OtherAttachements = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubAttachement"));
	OtherAttachements->SetupAttachment(WeaponMesh);

	//Weapon Struct 
	WeaponStruct.WeaponName = "Base Weapon";
	WeaponStruct.SocketName = FName("Default");
	WeaponStruct.WeaponImage = nullptr;
	WeaponStruct.WeaponType = EWeaponType::Default;
	WeaponStruct.FireMontages_ADS = nullptr;
	WeaponStruct.FireMontages_Idle = nullptr;
	WeaponStruct.Weapon_Fire_Montage = nullptr;
	WeaponStruct.Weapon_Reload_Montage = nullptr;

}

// Called when the game starts or when spawned
void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
	CharacterRef = Cast<AMalan>(PlayerController->GetPawn());
}
// Called every frames
void AWeapon_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//This function Only Run on Sniper Child Class
void AWeapon_Base::RenderScope()
{
	if (CharacterRef)
	{
		if (CharacterRef->isAimDownSight)
		{
			NonScope->SetHiddenInGame(true, false);
			Scope->SetHiddenInGame(false, false);
			if (PlayerController)
			{
				PlayerController->SetDeprecatedInputYawScale(ScopeSensitivity);
				PlayerController->SetDeprecatedInputPitchScale(ScopeSensitivity);
			}
		}
		else
		{
			Scope->SetHiddenInGame(true, false);
			NonScope->SetHiddenInGame(false, false);
			if (PlayerController)
			{
				PlayerController->SetDeprecatedInputYawScale(NormalSensitivity);
				PlayerController->SetDeprecatedInputPitchScale(NormalSensitivity);
			}
		}
	}
}