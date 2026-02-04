// Fill out your copyright notice in the Description page of Project Settings.


#include "WingsOfBetrayal/Other/Bullet_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet_Base::ABullet_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SphereCollider->SetupAttachment(RootComponent);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	MeshComp->SetupAttachment(SphereCollider);

	ProjectTile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectTile->UpdatedComponent = SphereCollider;
}

// Called when the game starts or when spawned
void ABullet_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}
