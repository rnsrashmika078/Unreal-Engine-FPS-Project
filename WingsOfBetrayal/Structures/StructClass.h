#pragma once

#include "CoreMinimal.h"
#include "WingsOfBetrayal/Enumarators/EnumClass.h"
#include "StructClass.generated.h"

USTRUCT(BlueprintType)
struct FWeaponStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UTexture2D* WeaponImage;


	//Character Mesh Animations
	UPROPERTY(EditAnywhere, Category = "Character Animation: Weapon Fire Anim Montages")
	UAnimMontage* FireMontages_Idle;

	UPROPERTY(EditAnywhere, Category = "Character Animation: Weapon Fire Anim Montages")
	UAnimMontage* FireMontages_ADS;

	UPROPERTY(EditAnywhere, Category = "Weapon Animation: Weapon Reload Anim Montage")
	UAnimMontage* ReloadMontage_ADS;

	UPROPERTY(EditAnywhere, Category = "Weapon Animation: Weapon Reload Anim Montage")
	UAnimMontage* ReloadMontage_NO_ADS;


	//Weapon Mesh Animations 
	UPROPERTY(EditAnywhere, Category = "Weapon Animation: Weapon Fire Anim Montages")
	UAnimMontage* Weapon_Fire_Montage; 

	UPROPERTY(EditAnywhere, Category = "Weapon Animation: Weapon Reload Anim Montage")
	UAnimMontage* Weapon_Reload_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName SocketName;


	// Default constructor with initialization
	FWeaponStruct()
		: WeaponName(TEXT("Base Weapon"))
		, WeaponType(EWeaponType::Default)
		, WeaponImage(nullptr)
		, SocketName(TEXT("DefaultSocket"))
		//{
		//	// Log a message when the struct is constructed
		//	UE_LOG(LogTemp, Warning, TEXT("FWeaponStruct created with WeaponName: %s"), *WeaponName);
		//}

		//// Method to display weapon details
		//FString GetWeaponDetails() const
		//{
		//	return FString::Printf(TEXT("Weapon: %s, Type: %s"), *WeaponName, *UEnum::GetDisplayValueAsText(WeaponType).ToString());
		//}
	{

	}
};
