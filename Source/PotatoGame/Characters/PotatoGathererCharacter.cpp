#include "PotatoGathererCharacter.h"

#include "Components/PotatoPickUpComponent.h"

APotatoGathererCharacter::APotatoGathererCharacter()
{
	PotatoPickUpComponent = CreateDefaultSubobject<UPotatoPickUpComponent>(TEXT("PotatoPickUpComponent"));
	PotatoPickUpComponent->SetupAttachment(RootComponent);
}
