#include "PixelShipPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APixelShipPlayer::APixelShipPlayer()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	PixelShip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PixelShip"));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(PixelShip);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(PixelShip);
	SpringArm->TargetArmLength = 250.0f;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}


void APixelShipPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void APixelShipPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APixelShipPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

