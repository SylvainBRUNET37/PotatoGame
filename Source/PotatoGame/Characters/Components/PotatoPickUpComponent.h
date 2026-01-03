#pragma once

#include "CoreMinimal.h"
#include "PotatoPickUpComponent.generated.h"

class APotato;

UCLASS(meta=(BlueprintSpawnableComponent))
class UPotatoPickUpComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UPotatoPickUpComponent();
	
	[[nodiscard]] bool IsHoldingPotato() const;
	APotato* GetAndDropPotato();
	
protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
private:
	UPROPERTY(EditAnywhere)
	FName HeldSocketName = FName("socket_hand_r");
	
	UPROPERTY(Transient)
	APotato* HeldPotato;
	
	UFUNCTION()
	void OnOwnerOverlap(AActor* OwningActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnOwnerHit(AActor* OwningActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	
	void OnSetupPlayerInput(UInputComponent* InputComponent);
	void PickupPotato(APotato* Potato);
	void SetHeldPotato(APotato* Potato);
	void DropPotato();
};
