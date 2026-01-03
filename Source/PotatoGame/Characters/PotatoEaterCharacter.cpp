#include "PotatoEaterCharacter.h"

#include "Components/PotatoEatingComponent.h"
#include "Components/PotatoPickUpComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Net/UnrealNetwork.h"

APotatoEaterCharacter::APotatoEaterCharacter()
{
	PotatoPickUpComponent = CreateDefaultSubobject<UPotatoPickUpComponent>(TEXT("PotatoPickUpComponent"));
	PotatoPickUpComponent->SetupAttachment(RootComponent);
	
	PotatoEatingComponent = CreateDefaultSubobject<UPotatoEatingComponent>(TEXT("PotatoEatingComponent"));
	PotatoEatingComponent->SetupAttachment(RootComponent);
}

void APotatoEaterCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APotatoEaterCharacter, _currentScale);
}

void APotatoEaterCharacter::BeginPlay()
{
	Super::BeginPlay();

	_springArmComponent = FindComponentByClass<USpringArmComponent>();
	_initialSpringArmLenght = _springArmComponent->TargetArmLength;
}

void APotatoEaterCharacter::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
}
