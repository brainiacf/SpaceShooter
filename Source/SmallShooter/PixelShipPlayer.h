#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"


#include "PixelShipPlayer.generated.h"


class UStaticMeshComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class SMALLSHOOTER_API APixelShipPlayer : public APawn
{
	GENERATED_BODY()

public:
	
	APixelShipPlayer();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UStaticMeshComponent*PixelShip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UArrowComponent*Arrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	USpringArmComponent*SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UCameraComponent*Camera;

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
