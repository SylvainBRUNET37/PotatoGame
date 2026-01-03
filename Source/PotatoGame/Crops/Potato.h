#pragma once

#include "CoreMinimal.h"
#include "NutritionalInformations.h"
#include "Potato.generated.h"

UCLASS()
class POTATOGAME_API APotato : public AActor
{
	GENERATED_BODY()
	
public:
	[[nodiscard]] const FNutritionalInformations& GetNutritionalInformations() const
	{
		return NutritionalInformations;
	}
	
private:
	UPROPERTY(EditAnywhere)
	float Weight;
	
	UPROPERTY(EditAnywhere)
	FNutritionalInformations NutritionalInformations;
};
