#include "PixelShipController.h"
#include "Engine/LocalPlayer.h" // For ULocalPlayer

#include "EnhancedInputSubsystems.h" 





APixelShipController::APixelShipController()
{
    PlayerInput = CreateDefaultSubobject<UEnhancedInputComponent>(TEXT("PlayerInput"));
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

    
}
void APixelShipController::MoveForward(const FInputActionValue& ActionValue)
{
    UE_LOG(LogTemp, Warning, TEXT("MoveForward"));
}
void APixelShipController::BeginPlay()
{
    Super::BeginPlay();
    PlayerInput->BindAction("MoveForward", ETriggerEvent::Triggered, this, &APixelShipController::MoveForward);
    if (Subsystem )
    {
       Subsystem->AddMappingContext(IM_PixelShip,0);
    }
    
    
}