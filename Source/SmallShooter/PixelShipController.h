

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"



#include "PixelShipController.generated.h"

/**
 * 
 */
UCLASS()
class SMALLSHOOTER_API APixelShipController : public APlayerController
{
	GENERATED_BODY()
	APixelShipController();

public:
UEnhancedInputComponent* PlayerInput;
UInputAction* MoveForward= Cast<UInputAction>(InputMappingContext->FindMapping("MoveForward"));


public:
virtual void BeginPlay() override;


private:
void MoveForward(const FInputActionValue& ActionValue);

	
	
};
