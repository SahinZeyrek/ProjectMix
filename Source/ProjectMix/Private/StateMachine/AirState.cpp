// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/AirState.h"
#include "StateMachine/StateMachineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Attack/AttackComponent.h"
#include "ProjectMix/ProjectMixCharacter.h"

	void UAirState::StateEnter(AProjectMixCharacter* character)
	{
		UBaseState::StateEnter(character);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Entering Air State"));
		ownerAttackComponent = PlayerChar->GetComponentByClass<UAttackComponent>();
		if (ownerAttackComponent)
		{
			ownerAttackComponent->OnAttackDelegate.AddUniqueDynamic(this, &UAirState::StopGravity);
			ownerAttackComponent->EnterAerialMode();
		}
	}

void UAirState::StateUpdate(AProjectMixCharacter* character, float deltaTime)
{
	if (!PlayerChar->GetCharacterMovement()->IsFalling())
	{
		ownerStateMachineComp->SetState(ownerStateMachineComp->RequestState("Run"), PlayerChar);
	}
}

void UAirState::StateExit(AProjectMixCharacter* character)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Exiting Air State"));
	if (ownerAttackComponent)
	{
		ownerAttackComponent->ExitAerialMode();
	}
}

void UAirState::HandleInput(AProjectMixCharacter* character, const FInputActionValue& input)
{
}

void UAirState::StopGravity()
{
	// Disable gravity
	PlayerChar->GetCharacterMovement()->GravityScale = 0.0f;

	// Stop vertical movement (Z-axis)
	FVector CurrentVelocity = PlayerChar->GetCharacterMovement()->Velocity;
	CurrentVelocity.Z = 0.0f;  // Set the vertical velocity to 0 to prevent floating
	PlayerChar->GetCharacterMovement()->Velocity = CurrentVelocity;
}
