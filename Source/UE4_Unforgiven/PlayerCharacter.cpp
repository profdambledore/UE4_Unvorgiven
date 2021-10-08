// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "PlayerHUD.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set Location and Rotation of the player Mesh
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Find the Player Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>PlayerMeshObject(TEXT("/Game/Player/Mesh/SK_Mannequin"));
	if (PlayerMeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMeshObject.Object);
	}

	// Far Camera
	FarSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Far Spring Arm"));
	FarSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	FarSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	FarSpringArm->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	FarSpringArm->TargetArmLength = 800.0f;

	FarCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Far Person Camera"));
	FarCamera->SetupAttachment(FarSpringArm, USpringArmComponent::SocketName);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get refernce to the player controller
	PC = Cast<APlayerController>(GetController());
	
	// Get reference to the player HUD
	HUDRef = Cast<APlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	//HUDRef->SetPlayerRef(this);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If strafing, rotate to match to the camera rotation
	if (bIsStrafe == true)
	{
		FRotator CtrlRot = GetControlRotation();
		CtrlRot.Pitch = 0.0f; CtrlRot.Roll = 0.0f;
		SetActorRotation(CtrlRot);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Axis Binds
	PlayerInputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveY);
	PlayerInputComponent->BindAxis("RotateCameraX", this, &APlayerCharacter::RotateCameraX);
	PlayerInputComponent->BindAxis("RotateCameraY", this, &APlayerCharacter::RotateCameraY);

	// Add Action Binds
	PlayerInputComponent->BindAction("Strafe", IE_Pressed, this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAction("Strafe", IE_Released, this, &APlayerCharacter::Strafe);
}

void APlayerCharacter::MoveX(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		// Move on the X axis based on the controller's yaw value
		FRotator CtrlRot = GetControlRotation();
		CtrlRot.Pitch = 0.0f; CtrlRot.Roll = 0.0f;
		AddMovementInput(UKismetMathLibrary::GetForwardVector(CtrlRot), AxisValue, false);
	}
}

void APlayerCharacter::MoveY(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		// Move on the Y axis based on the controller's yaw value
		FRotator CtrlRot = GetControlRotation();
		CtrlRot.Pitch = 0.0f; CtrlRot.Roll = 0.0f;
		AddMovementInput(UKismetMathLibrary::GetRightVector(CtrlRot), AxisValue, false);
	}
}

void APlayerCharacter::RotateCameraX(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		// Rotate on the X axis based on the input's axis value
		AddControllerYawInput(AxisValue);
	}
}

void APlayerCharacter::RotateCameraY(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		// Rotate on the Y axis based on the input's axis value
		AddControllerPitchInput(AxisValue);
	}
}

void APlayerCharacter::Strafe()
{
	if (bIsStrafe == true)
	{
		bIsStrafe = false;
	}
	else if (bIsStrafe == false)
	{
		bIsStrafe = true;
	}
}

