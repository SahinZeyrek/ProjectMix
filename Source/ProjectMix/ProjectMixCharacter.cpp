// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectMixCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "StateMachine/StateMachineComponent.h"
#include "StateMachine/IdleState.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjectMixCharacter

AProjectMixCharacter::AProjectMixCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 2400.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	StateMachineComponent = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine"));
	
	//IdleState = CreateDefaultSubobject<UIdleState>(TEXT("IdleState"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AProjectMixCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	StateMachineComponent->SetState(StateMachineComponent->RequestState(TEXT("Idle")), this);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectMixCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	InputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputComponent) {
		
		// Jumping
		FEnhancedInputActionEventBinding* JumpStartBinding = &InputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		FEnhancedInputActionEventBinding* JumpStopBinding = &InputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		FEnhancedInputActionEventBinding* MoveBinding = &InputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectMixCharacter::Move);

		// Looking
		FEnhancedInputActionEventBinding* LookBinding = &InputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectMixCharacter::Look);

		// Store the bindings
		ActionBindings.Add(JumpStartBinding);
		ActionBindings.Add(JumpStopBinding);
		ActionBindings.Add(MoveBinding);
		ActionBindings.Add(LookBinding);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectMixCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProjectMixCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Black, LookAxisVector.ToString());
	//LookAxisVector.Normalize();
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjectMixCharacter::BindDefaultActions()
{
	if (InputComponent)
	{
		for (const FEnhancedInputActionEventBinding* Binding : ActionBindings)
		{
			bool b = InputComponent->RemoveBindingByHandle((*Binding).GetHandle());
			if (b)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("removed bindings"));
			}
		}

		// Clear the stored bindings to ensure they are not used later
		ActionBindings.Empty();
	}
	SetupPlayerInputComponent(InputComponent);
}
