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
	

	FVector ForwardDirection;
	FVector RightDirection;
	FVector DirectionVec;
	
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
	//	

	/*Curve Values*/
	float CurveValueForward;
	float CurveValueRight;
	float CurveValueBrake;
	//

	/*Timer Delegate*/
	FTimerHandle DecelerationTimerHandle;

protected:

	virtual void BeginPlay() override;

	/*Movement Methods*/
	void MoveForward(const FInputActionValue& Value);
	void MoveForward_RE(const FInputActionValue& Value);
    void MoveRight(const FInputActionValue& Value);
	//
	
public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
