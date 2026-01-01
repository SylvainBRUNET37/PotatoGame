#include "PotatoPlanterCharacter.h"

#include "Components/InputComponent.h"
#include "Components/PotatoPickUpComponent.h"
#include "Components/PotatoPlantingComponent.h"

APotatoPlanterCharacter::APotatoPlanterCharacter()
{
	PotatoPlantingComponent = CreateDefaultSubobject<UPotatoPlantingComponent>(TEXT("PotatoPlantComponent"));
	PotatoPlantingComponent->SetupAttachment(RootComponent);
	
	PotatoPickUpComponent = CreateDefaultSubobject<UPotatoPickUpComponent>(TEXT("PotatoPickUpComponent"));
	PotatoPickUpComponent->SetupAttachment(RootComponent);
}
