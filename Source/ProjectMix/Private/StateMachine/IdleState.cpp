// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/IdleState.h"
#include "StateMachine/StateMachineComponent.h"
#include "ProjectMix/ProjectMixCharacter.h"

void UIdleState::StateEnter(AProjectMixCharacter* character)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, TEXT("Entering Idle State"));

	// TO DO. CHANGE FUNCTION BINDIUNGS TO ACTION. UNBIND CURRENT ACTIONS.
	// Set up action bindings
	//character->GetInputComponent()->ClearActionValueBindings();
	UEnhancedInputComponent* inputComp = character->GetInputComponent();
	inputComp->ClearActionBindings();
	//inputComp->ClearActionValueBindings();

	PlayerChar = character;
	if (inputComp) {

		// Jumping
		inputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &UIdleState::Jump);
		inputComp->BindAction(JumpAction, ETriggerEvent::Completed, this, &UIdleState::StopJumping);

		// Moving
		inputComp->BindActionValue(MoveAction);
		inputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UIdleState::Move);

		
		// Looking
		inputComp->BindActionValue(LookAction);
		inputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &UIdleState::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void UIdleState::StateUpdate(AProjectMixCharacter* character, float deltaTime)
{
	// State dependent logic
	if (character->GetVelocity().Length() > 0)
	{
		//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Green, TEXT("Player velocity is higher than 0"));
		UStateMachineComponent* comp = character->GetComponentByClass<UStateMachineComponent>();
		comp->SetState(comp->RequestState("Run"),PlayerChar);
	}
}

void UIdleState::StateExit(AProjectMixCharacter* character)
{
	// UNBIND all current actions
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, TEXT("Exiting State Idle"));

	//character->GetInputComponent()->ClearBindingsForObject(character);

}

void UIdleState::HandleInput(AProjectMixCharacter* character, const FInputActionValue& input)
{
	// State dependent Input
}

void UIdleState::Jump()
{
	PlayerChar->Jump();
}

void UIdleState::StopJumping()
{
	PlayerChar->StopJumping();
}

void UIdleState::Move()
{
	PlayerChar->Move(PlayerChar->GetInputComponent()->GetBoundActionValue(MoveAction));
}

void UIdleState::Look()
{
	PlayerChar->Look(PlayerChar->GetInputComponent()->GetBoundActionValue(LookAction));
}

