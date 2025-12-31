#pragma once

#include "CoreMinimal.h"
#include "NutritionalInformations.h"
#include "Potato.generated.h"

UCLASS()
class APotato : public AActor
{
public:
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float Weight;
	
	UPROPERTY(EditAnywhere)
	FNutritionalInformations NutritionalInformations;
};
