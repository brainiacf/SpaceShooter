#include "PixelShipPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

APixelShipPlayer::APixelShipPlayer()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	PixelShip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PixelShip"));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(PixelShip);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(PixelShip);
	//23.197985 capsule half height
	//23.197985 capsule radius

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Capsule);
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

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

}


void APixelShipPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ThisClass::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ThisClass::MoveRight);

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
	if(Controller != nullptr && Arrow != nullptr )
	{
		if(InputValue != 0.0f){ ForwardDirection = Arrow->GetForwardVector() * MovementSpeed * InputValue ;}
		
		PixelShip->SetPhysicsLinearVelocity(ForwardDirection);
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ForwardDirection: %s"), *ForwardDirection.ToString()));
	}
}

void APixelShipPlayer::MoveRight(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	if (Controller != nullptr && Arrow !=nullptr)
	{
		if (InputValue != 0.0f) { RightDirection = Arrow->GetRightVector() * MovementSpeed * InputValue; }
		PixelShip->SetPhysicsLinearVelocity(RightDirection);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("RightDirection: %s"), *RightDirection.ToString()));
	}
}

