#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Default UMETA(DisplayName = "Default"),
    Pistol UMETA(DisplayName = "Pistol"),          
    SniperRifle UMETA(DisplayName = "SR"),
    AssultRifle UMETA(DisplayName = "AR"), 
};
