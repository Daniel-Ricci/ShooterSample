// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSampleCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ShooterSample.h"
#include "ShooterSamplePlayerController.h"

AShooterSampleCharacter::AShooterSampleCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 250.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	// Set max walking speeds
	MaxWalkingSpeed = GetCharacterMovement()->MaxWalkSpeed;
	MaxWalkingSpeedCrouched = GetCharacterMovement()->MaxWalkSpeedCrouched;
	
	// Set camera distance
	CameraDefaultDistance = CameraBoom->TargetArmLength;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AShooterSampleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
	bIsAlive = true;
	UpdateHUD();
	
	OnTakeAnyDamage.AddDynamic(this, &AShooterSampleCharacter::OnDamageTaken);
	
	GetMesh()->HideBoneByName("weapon_r", EPhysBodyOp::PBO_None);

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	if(Gun)
	{
		Gun->SetOwner(this);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->OwnerController = GetController();
	}
}

void AShooterSampleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterSampleCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AShooterSampleCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterSampleCharacter::Look);
		
		// Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AShooterSampleCharacter::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AShooterSampleCharacter::Aim);
		
		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AShooterSampleCharacter::Shoot);
	}
	else
	{
		UE_LOG(LogShooterSample, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AShooterSampleCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AShooterSampleCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AShooterSampleCharacter::Aim(const FInputActionValue& Value)
{
	// input is a boolean
	bool IsAiming = Value.Get<bool>();

	// route the input
	DoAim(IsAiming);
}

void AShooterSampleCharacter::Shoot(const FInputActionValue& Value)
{
	DoShoot();
}

void AShooterSampleCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AShooterSampleCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AShooterSampleCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AShooterSampleCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AShooterSampleCharacter::DoAim(bool Aim)
{
	bIsAiming = Aim;
	GetCharacterMovement()->MaxWalkSpeed = Aim ? MaxWalkingSpeedCrouched : MaxWalkingSpeed;
	CameraBoom->TargetArmLength = Aim ? CameraDefaultDistance - 100.0f: CameraDefaultDistance;
}

void AShooterSampleCharacter::DoShoot()
{
	Gun->PullTrigger();
}

void AShooterSampleCharacter::UpdateHUD()
{
	AShooterSamplePlayerController* PlayerController = Cast<AShooterSamplePlayerController>(GetController());
	if (PlayerController)
	{
		float NewPercent = CurrentHealth / MaxHealth;
		if (NewPercent <= 0.0f)
		{
			NewPercent = 0.0f;
		}
		PlayerController->HUDWidget->SetHealthBarPercent(NewPercent);
	}
}

void AShooterSampleCharacter::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (bIsAlive)
	{
		CurrentHealth -= Damage;
		UpdateHUD();
		
		if (CurrentHealth <= 0.0f)
		{
			bIsAlive = false;
			CurrentHealth = 0.0f;
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			DetachFromControllerPendingDestroy();
		}
	}
}
