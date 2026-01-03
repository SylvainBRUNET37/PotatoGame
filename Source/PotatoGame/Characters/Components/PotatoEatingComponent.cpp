#include "PotatoEatingComponent.h"

#include "PotatoPickUpComponent.h"
#include "PotatoGame/Characters/PotatoBaseCharacter.h"
#include "PotatoGame/Crops/Potato.h"

UPotatoEatingComponent::UPotatoEatingComponent()
{
	bWantsInitializeComponent = true;
}

void UPotatoEatingComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	// Enregistrer UPotatoEatingComponent::OnSetupPlayerInput sur 
	// l'évènement APotatoBaseCharacter::OnSetupPlayerInput du owner
	APotatoBaseCharacter* Owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(Owner)))
	{	
		Owner->OnSetupPlayerInput.AddUObject(this, &UPotatoEatingComponent::OnSetupPlayerInput);
	}
}

void UPotatoEatingComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	
	// Désenregistrer UPotatoEatingComponent::OnSetupPlayerInput de 
	// l'évènement APotatoBaseCharacter::OnSetupPlayerInput du owner
	APotatoBaseCharacter* Owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(Owner)))
	{	
		Owner->OnSetupPlayerInput.RemoveAll(this);
	}
}

void UPotatoEatingComponent::OnSetupPlayerInput(UInputComponent* InputComponent)
{
	// Binder l'input 'Fire' sur la méthode UPotatoEatingComponent::EatHeldPotato
	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &UPotatoEatingComponent::EatHeldPotato);
}

void UPotatoEatingComponent::EatHeldPotato()
{
	// Récupere le PotatoPickUpComponent du owner
	const APotatoBaseCharacter* Owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (not ensure(IsValid(Owner)))
		return;
	
	UPotatoPickUpComponent* PotatoPickUpComponent = Owner->FindComponentByClass<UPotatoPickUpComponent>();
	if (not ensure(IsValid(PotatoPickUpComponent)) || not PotatoPickUpComponent->IsHoldingPotato())
		return;
	
	// Si UPotatoPickUpComponent::IsHoldingPotato())
	// Invoquer UPotatoPickUpComponent::Authority_DropPotato() pour relâcher et obtenir la potato
	//Invoquer EatPotato(potato)
	APotato* HeldPotato = PotatoPickUpComponent->GetAndDropPotato();
	EatPotato(HeldPotato);
}

void UPotatoEatingComponent::EatPotato(APotato* Potato)
{ 	
	if (not ensure(IsValid(Potato)))
		return;
	
	// Augmenter CaloriesEaten par APotato::NutritionalInformation::Calories
	CaloriesEaten += Potato->GetNutritionalInformations().Calories;
	
	// Invoquer AActor::Destroy() sur la potato pour la détruire
	Potato->Destroy();
}
