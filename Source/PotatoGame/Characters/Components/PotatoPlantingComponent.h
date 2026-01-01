#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "PotatoPlantingComponent.generated.h"

class APotato;
class UInputComponent;

UCLASS(meta=(BlueprintSpawnableComponent))
class POTATOGAME_API UPotatoPlantingComponent : public USceneComponent
{	
	GENERATED_BODY()
	
public:
	UPotatoPlantingComponent();
	
protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
private:
	UPROPERTY(EditAnywhere)
	FName SpawnSocketName = TEXT("socket_spawn");
	
	UPROPERTY(EditAnywhere)
	float SpawnVelocity;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APotato> PotatoType;
	
	void OnSetupPlayerInput(UInputComponent* InputComponent);
	void PlantPotato();
};
