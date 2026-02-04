// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WingsOfBetrayal/Enumarators/EnumClass.h"
#include "MalanAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class WINGSOFBETRAYAL_API UMalanAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

	UMalanAnimationInstance();
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMalan* CharacterRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator AimOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool AimDownSight;
};
