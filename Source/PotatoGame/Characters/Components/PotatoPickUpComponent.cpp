#include "PotatoPickUpComponent.h"

#include "PotatoGame/Characters/PotatoBaseCharacter.h"
#include "PotatoGame/Crops/Potato.h"

UPotatoPickUpComponent::UPotatoPickUpComponent()
{
	bWantsInitializeComponent = true;
}

void UPotatoPickUpComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	// Enregistrer UPotatoPickUpComponent::OnSetupPlayerInput sur l'évènement APotatoBaseCharacter::OnSetupPlayerInput du owner
	// Enregistrer UPotatoPickUpComponent::OnOwnerOverlap sur l'évènement  APotatoBaseCharacter::OnActorBeginOverlap du owner
	// Enregistrer UPotatoPickUpComponent::OnOwnerHwwwit sur l'évènement  APotatoBaseCharacter::OnActorHit du owner
	APotatoBaseCharacter* Owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(Owner)))
	{	
		Owner->OnSetupPlayerInput.AddUObject(this, &UPotatoPickUpComponent::OnSetupPlayerInput);
		Owner->OnActorBeginOverlap.AddDynamic(this, &UPotatoPickUpComponent::OnOwnerOverlap);
		Owner->OnActorHit.AddDynamic(this, &UPotatoPickUpComponent::OnOwnerHit);
	}
}

void UPotatoPickUpComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	
	// Désenregistrer UPotatoPickUpComponent::OnSetupPlayerInput sur l'évènement APotatoBaseCharacter::OnSetupPlayerInput du owner
	// Désenregistrer UPotatoPickUpComponent::OnOwnerOverlap sur l'évènement  APotatoBaseCharacter::OnActorBeginOverlap du owner
	// Désenregistrer UPotatoPickUpComponent::OnOwnerHit sur l'évènement  APotatoBaseCharacter::OnActorHit du owner
	APotatoBaseCharacter* Owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(Owner)))
	{
		Owner->OnActorBeginOverlap.RemoveDynamic(this, &UPotatoPickUpComponent::OnOwnerOverlap);
		Owner->OnActorHit.RemoveDynamic(this, &UPotatoPickUpComponent::OnOwnerHit);
		Owner->OnSetupPlayerInput.RemoveAll(this);
	}
}

void UPotatoPickUpComponent::OnSetupPlayerInput(UInputComponent* InputComponent)
{
	// Binder l'input 'Release' sur la méthode UPotatoPickUpComponent::DropPotato()
	InputComponent->BindAction(TEXT("Release"), IE_Pressed, this, &UPotatoPickUpComponent::DropPotato);
}

void UPotatoPickUpComponent::OnOwnerOverlap(AActor*, AActor* OtherActor)
{
	// Si OtherActor est un APotato, invoquer PickupPotato()
	if (OtherActor->IsA<APotato>())
		PickupPotato(Cast<APotato>(OtherActor));
}

void UPotatoPickUpComponent::OnOwnerHit(AActor*, AActor* OtherActor, FVector, const FHitResult&)
{
	// Si OtherActor est un APotato, invoquer PickupPotato()
	if (OtherActor->IsA<APotato>())
		PickupPotato(Cast<APotato>(OtherActor));
}

void UPotatoPickUpComponent::PickupPotato(APotato* Potato)
{
	// Si IsHoldingPotato() est faux, alors invoquer SetHeldPotato(potato)
	if (!IsHoldingPotato())
		SetHeldPotato(Potato);
}

void UPotatoPickUpComponent::DropPotato()
{
	// Si IsHoldingPotato() est vrai, alors invoquer SetHeldPotato(null)
	if (IsHoldingPotato())
		SetHeldPotato(nullptr);
}

bool UPotatoPickUpComponent::IsHoldingPotato() const
{
	// Informer si HeldPotato est assigné
	return IsValid(HeldPotato);
}

void UPotatoPickUpComponent::SetHeldPotato(APotato* Potato)
{
	// Définir previous = HeldPotato
	APotato* PreviousPotato = HeldPotato;
	
	// Assigner HeldPotato = potato
	HeldPotato = Potato;
	
	// Si HeldPotato est défini, désactiver physique + collision sur HeldPotato 
	// et attacher HeldPotato au socket HeldSocketName
	if (IsValid(HeldPotato))
	{
		UPrimitiveComponent* HeldPotatoPrimitiveComponent = 
			Cast<UPrimitiveComponent>(HeldPotato->GetRootComponent());
		
		HeldPotatoPrimitiveComponent->SetSimulatePhysics(false);
		HeldPotatoPrimitiveComponent->SetEnableGravity(false);
		HeldPotatoPrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		// Récuperer le socket SpawnSocketName sur le modèle
		const APotatoBaseCharacter* Character = Cast<APotatoBaseCharacter>(GetOwner());
		if (ensure(IsValid(Character)))
		{
			USkeletalMeshComponent* MeshComponent = Character->GetMesh();
			if (ensure(IsValid(MeshComponent)) && ensure(MeshComponent->DoesSocketExist(HeldSocketName)))
			{
				// Attacher la patate au socket
				HeldPotato->AttachToComponent(
					MeshComponent,
					FAttachmentTransformRules::SnapToTargetNotIncludingScale,
					HeldSocketName
				);
			}
		}
	}
	
	// Si previous est défini, activer physique + collision sur previous et détacher previous du socket heldSocketName
	if (IsValid(PreviousPotato))
	{
		UPrimitiveComponent* TargetComponent = Cast<UPrimitiveComponent>(PreviousPotato->GetRootComponent());

		FDetachmentTransformRules DetachementRules = FDetachmentTransformRules::KeepWorldTransform;
		DetachementRules.ScaleRule = EDetachmentRule::KeepRelative;
		PreviousPotato->DetachFromActor(DetachementRules);

		TargetComponent->SetSimulatePhysics(true);
		TargetComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		TargetComponent->SetEnableGravity(true);
	}
}
