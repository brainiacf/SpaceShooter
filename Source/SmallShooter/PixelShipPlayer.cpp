#include "PixelShipPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Curves/CurveFloat.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

APixelShipPlayer::APixelShipPlayer()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	// /*Root Scene Component*/
	// Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// SetRootComponent(Root);	

	PixelShip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PixelShip"));

	

	
	/*Initialize Arrow Components*/
	BlueArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BlueArrow"));
	BlueArrow->ArrowColor = FColor::Blue;
	//BlueArrow->SetWorldScale3D(FVector(0.5f,0.5f,0.5f));
	BlueArrow->AttachToComponent(PixelShip,FAttachmentTransformRules::KeepWorldTransform);
	GreenArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("GreenArrow"));
	GreenArrow->ArrowColor = FColor::Green;
	GreenArrow->AttachToComponent(PixelShip,FAttachmentTransformRules::KeepWorldTransform);
	//GreenArrow->SetWorldScale3D(FVector(0.5f,0.5f,0.5f));
	
	RedArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RedArrow"));
	RedArrow->ArrowColor = FColor::Red;
	RedArrow->AttachToComponent(PixelShip,FAttachmentTransformRules::KeepWorldTransform);
	//RedArrow->SetWorldScale3D(FVector(0.5f,0.5f,0.5f));
	
	//
	
	/*SpringArom Component*/
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(PixelShip);
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeRotation(FRotator(90,0.0f,0.0f));
	//
	/*Camera Component*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	//
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(PixelShip);
	//23.197985 capsule half height
	//23.197985 capsule radius
	//UFloatingPawnMovement* FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	
}


void APixelShipPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	
}

void APixelShipPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PixelShipRotation = PixelShip->GetComponentRotation();
	GreenArrow->SetRelativeRotation(FRotator(PixelShipRotation.Roll,GreenArrow->GetComponentRotation().Yaw,GreenArrow->GetComponentRotation().Roll));

}


void APixelShipPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		/*Moving*/
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ThisClass::MoveForward);
		
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ThisClass::MoveRight);

		EnhancedInputComponent->BindAction(MoveForwardAction,ETriggerEvent::Completed, this, &ThisClass::MoveForward);

		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Completed, this, &ThisClass::MoveRight_RE);
		// Looking
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEnhancedInputDeleteCharacter::Look);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT(" Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."));
	}
}


void APixelShipPlayer::MoveForward(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	HoldStartTime = GetWorld()->GetTimeSeconds();
	//
	if(AccelerationFloatCurve != nullptr){CurveValueForward = AccelerationFloatCurve->GetFloatValue(HoldStartTime);}
	//
	if(Controller != nullptr && RedArrow != nullptr )
	{
		if(InputValue != 0.0f){ ForwardDirection = RedArrow->GetForwardVector() * MovementSpeed * InputValue* CurveValueForward ;}
		
		PixelShip->SetPhysicsLinearVelocity(ForwardDirection,true);
	
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("InputValue: %f"),InputValue));
	}

	
}

void APixelShipPlayer::MoveRight(const FInputActionInstance& Instance)
{
	float InputValue = Instance.GetValue().Get<float>();
	float ElapsedTime = Instance.GetElapsedTime();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("TIme: %f"),HoldStartTime_MoveRight));
	//
	if(AccelerationFloatCurve != nullptr){CurveValueRight = AccelerationFloatCurve->GetFloatValue(ElapsedTime);}
	if(BrakeFloatCurve != nullptr){CurveValueBrake = BrakeFloatCurve->GetFloatValue(ElapsedTime);}
	if(RotationFloatCurve != nullptr){CurveValueRotation = RotationFloatCurve->GetFloatValue(ElapsedTime);}
	//
	if (Controller != nullptr && GreenArrow !=nullptr)
	{	
		RightDirection = GreenArrow->GetForwardVector();
	
		if (InputValue != 0.0f) { DirectionVec = RightDirection * MovementSpeed * InputValue*CurveValueRight; }
	
		PixelShip->SetPhysicsLinearVelocity(DirectionVec,true);

		ShipRotation = PixelShip->GetComponentRotation();

		GreenArrowRotation = GreenArrow->GetComponentRotation();
		float TargetRotation = MaximumRotation*CurveValueRotation;
		
		float RollIntepTo = FMath::FInterpTo(GreenArrowRotation.Roll,TargetRotation*InputValue,GetWorld()->GetDeltaSeconds(),ShipIntertia);
		float ClampRollTo = FMath::Clamp(RollIntepTo,-MaximumRotation,MaximumRotation);
		if(ElapsedTime > 0.0f){
		PixelShip->SetRelativeRotation(
			FRotator(PixelShip->GetComponentRotation().Pitch,PixelShip->GetComponentRotation().Yaw,ClampRollTo),true);}
			

	}

}
void APixelShipPlayer::MoveRight_RE(const FInputActionInstance& Instance)
{
	float InputValue = Instance.GetValue().Get<float>();
	float ElapsedTime = Instance.GetElapsedTime();

	if (Controller != nullptr )
	{	
		
			PixelShip->SetRelativeRotation(FRotator(0.0,0.0,0.0),true);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("InputValue: %f"),InputValue));
		
	}
}

void APixelShipPlayer::MoveForward_RE(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	
	if (Controller != nullptr )
	{	

	}
}

