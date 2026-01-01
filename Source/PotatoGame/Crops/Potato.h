#pragma once

#include "CoreMinimal.h"
#include "NutritionalInformations.h"
#include "Potato.generated.h"

UCLASS()
class POTATOGAME_API APotato : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float Weight;
	
	UPROPERTY(EditAnywhere)
	FNutritionalInformations NutritionalInformations;
};
