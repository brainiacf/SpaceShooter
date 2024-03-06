#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"


#include "PixelShipPlayer.generated.h"


class UStaticMeshComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UCapsuleComponent;
struct FInputActionValue;

UCLASS()
class SMALLSHOOTER_API APixelShipPlayer : public APawn
{
	GENERATED_BODY()

public:
	
	APixelShipPlayer();
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UStaticMeshComponent*PixelShip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UArrowComponent*Arrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	USpringArmComponent*SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UCameraComponent*Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UCapsuleComponent* Capsule; // Added
	//
	UPROPERTY(EditAnywhere)
    float MovementSpeed = 500.0f;

	FVector ForwardDirection;
	FVector RightDirection;

	//

private:
	// Input Actions 
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveRightAction;
protected:

	virtual void BeginPlay() override;

	//
	void MoveForward(const FInputActionValue& Value);
    void MoveRight(const FInputActionValue& Value);
	//
public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
