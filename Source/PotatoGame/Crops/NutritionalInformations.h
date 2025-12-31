#pragma once

#include "CoreMinimal.h"
#include "NutritionalInformations.generated.h"

USTRUCT()
struct FNutritionalInformations
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float Calories;
	
	UPROPERTY(EditAnywhere)
	float Carbs;
	
	UPROPERTY(EditAnywhere)
	float Fat;
	
	UPROPERTY(EditAnywhere)
	float Proteins;
};
