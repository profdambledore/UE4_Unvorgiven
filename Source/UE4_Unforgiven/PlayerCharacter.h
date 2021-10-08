// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class UE4_UNFORGIVEN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	// FUNCTIONS
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Inputs
	// Axis
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void RotateCameraX(float AxisValue);
	void RotateCameraY(float AxisValue);

	//Action
	void Strafe();

	// VARIABLES
public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* FarCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* FarSpringArm;

	// Variables
	// References
	APlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class APlayerHUD* HUDRef;

	bool bIsStrafe = false;
};
