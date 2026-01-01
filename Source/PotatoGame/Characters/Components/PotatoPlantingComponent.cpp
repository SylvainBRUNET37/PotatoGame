#include "PotatoPlantingComponent.h"

#include "PotatoGame/Characters/PotatoBaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "PotatoGame/Crops/Potato.h"

UPotatoPlantingComponent::UPotatoPlantingComponent()
{
	bWantsInitializeComponent = true;
}

void UPotatoPlantingComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	// Enregistrer UPotatoPlantingComponent::OnSetupPlayerInput sur l'évènement 
	// APotatoBaseCharacter::OnSetupPlayerInput du owner
	APotatoBaseCharacter* Owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(Owner)))
		Owner->OnSetupPlayerInput.AddUObject(this, &UPotatoPlantingComponent::OnSetupPlayerInput);
}

void UPotatoPlantingComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	
	// Désenregistrer UPotatoPlantingComponent::OnSetupPlayerInput de 
	// l'évènement APotatoBaseCharacter::OnSetupPlayerInput du owner
	APotatoBaseCharacter* Owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(Owner)))
		Owner->OnSetupPlayerInput.RemoveAll(this);
}

void UPotatoPlantingComponent::OnSetupPlayerInput(UInputComponent* InputComponent)
{
	// Binder l'input 'Fire' sur la méthode UPotatoPlantingComponent::PlantPotato
	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &UPotatoPlantingComponent::PlantPotato);
}

void UPotatoPlantingComponent::PlantPotato()
{
	// Récuperer le socket SpawnSocketName sur le modèle
	const APotatoBaseCharacter* Character = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(Character)))
	{
		const USkeletalMeshComponent* MeshComponent = Character->GetMesh();
		if (ensure(IsValid(MeshComponent)) && ensure(MeshComponent->DoesSocketExist(SpawnSocketName)))
		{
			// Obtienir la world transform du socket
			FVector SocketLocation;
			FRotator SocketRotation;
			MeshComponent->GetSocketWorldLocationAndRotation(SpawnSocketName, SocketLocation, SocketRotation);
			
			// Rotation aléatoire sur la patate
			SocketRotation = UKismetMathLibrary::RandomRotator(true);
			
			// Déterminer une vélocité aléatoire dans un cône face au personnage d'une magnitude SpawnVelocity
			SocketLocation += UKismetMathLibrary::RandomUnitVectorInConeInDegrees(
					Character->GetActorForwardVector(), 45.0f) * SpawnVelocity;
			
			// Instancier un actor Potato de type PotatoType à la transform et vélocité calculée
			GetWorld()->SpawnActor<APotato>(
				PotatoType,
				SocketLocation, 
				SocketRotation);
		}
	}
}
