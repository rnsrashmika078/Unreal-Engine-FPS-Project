// Fill out your copyright notice in the Description page of Project Settings.


#include "WingsOfBetrayal/AnimationClass/MalanAnimationInstance.h"
#include "WingsOfBetrayal/Characters/Main_Character/Malan.h"


UMalanAnimationInstance::UMalanAnimationInstance()
{
	AimDownSight = false;
}
void UMalanAnimationInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	CharacterRef = Cast<AMalan>(TryGetPawnOwner());
}

void UMalanAnimationInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (CharacterRef != nullptr) 
	{
	    AimOffset = CharacterRef->SpineRotation();
		AimDownSight = CharacterRef->isAimDownSight;
	}
	
}
