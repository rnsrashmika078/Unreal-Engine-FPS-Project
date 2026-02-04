// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WingsOfBetrayal/Structures/StructClass.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/World.h" 
#include "WingsOfBetrayal/Characters/Main_Character/Malan.h"
#include "Weapon_Base.generated.h"

UCLASS()
class WINGSOFBETRAYAL_API AWeapon_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class USkeletalMeshComponent* Scope;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* NonScope;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Capture")
	class USceneCaptureComponent2D* SceneCaptureComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* OtherAttachements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponStruct WeaponStruct;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float MaxZoomIn;
	float FieldOfView;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	AMalan* CharacterRef;

	APlayerController* PlayerController;

	UFUNCTION(BlueprintCallable)
	void RenderScope();

	float ScopeSensitivity;
	float NormalSensitivity;
};
