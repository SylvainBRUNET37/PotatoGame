#include "PotatoPlanterCharacter.h"

#include "PotatoGame/Gameplay/PotatoGameMode.h"

#include "Components/InputComponent.h"
#include "Components/PotatoPlantingComponent.h"


APotatoPlanterCharacter::APotatoPlanterCharacter()
{
	PotatoPlantingComponent = CreateDefaultSubobject<UPotatoPlantingComponent>(TEXT("PotatoPlantComponent"));
	PotatoPlantingComponent->SetupAttachment(RootComponent);
}
