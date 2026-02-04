// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet_Base.generated.h"


UCLASS()
class WINGSOFBETRAYAL_API ABullet_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* ProjectTile;
};
