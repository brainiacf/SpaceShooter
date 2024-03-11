/* the scariest thing in the world is the darkness in our hearts and how it erases the beauty in everything */

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"



#include "PixelShipPlayer.generated.h"

//
class UStaticMeshComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UCapsuleComponent;
class UCurveFloat;
//

//
struct FInputActionValue;
struct FInputActionInstance;

UCLASS()
class SMALLSHOOTER_API APixelShipPlayer : public APawn
{
	GENERATED_BODY()

public:
	
	APixelShipPlayer();
	/*StaticMeshComponent*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UStaticMeshComponent*PixelShip;

	/*ArrowComponent*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UArrowComponent*BlueArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArrowComponent")
	UArrowComponent*GreenArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArrowComponent")
	UArrowComponent*RedArrow;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	USpringArmComponent*SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UCameraComponent*Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip")
	UCapsuleComponent* Capsule; 
	
	/*Propertey for Movement*/
	UPROPERTY(EditAnywhere)
    float MovementSpeed = 500.0f;
	UPROPERTY(EditAnywhere)
	float MaximumRotation = 25.0f;
	UPROPERTY(EditAnywhere)
	float ShipIntertia = 500.0f;	
	

	FVector ForwardDirection;
	FVector RightDirection;
	FVector DirectionVec;

	FRotator ShipRotation;
	FRotator GreenArrowRotation;
	
	float HoldStartTime;
	float HoldEndTime;

	//

private:
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	//

	/*Input Actions*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveRightAction;
	//

	/*Float Curve*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* AccelerationFloatCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* BrakeFloatCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PixelShip", meta = (AllowPrivateAccess="true"))
	UCurveFloat* RotationFloatCurve;
	//	

	/*Curve Values*/
	float CurveValueForward;
	float CurveValueRight;
	float CurveValueBrake;
	float CurveValueRotation;
	//

protected:

	virtual void BeginPlay() override;

	/*Movement Methods*/ // [_RE-> Realeased]
	void MoveForward(const FInputActionValue& Value);
	void MoveForward_RE(const FInputActionValue& Value);
    void MoveRight(const FInputActionInstance& Instance);
	void MoveRight_RE(const FInputActionValue& Value);
	//

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
