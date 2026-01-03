#pragma once

#include "CoreMinimal.h"
#include "PotatoEatingComponent.generated.h"

class APotato;

UCLASS(meta=(BlueprintSpawnableComponent))
class UPotatoEatingComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:
	UPotatoEatingComponent();
	
private:
	UPROPERTY(Transient)
	float CaloriesEaten = 0.0f;
	
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
	void OnSetupPlayerInput(UInputComponent* InputComponent);
	void EatHeldPotato();
	void EatPotato(APotato* Potato);
};
