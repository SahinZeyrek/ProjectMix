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
	UBaseState::StateEnter(character);
	
}

void UIdleState::StateUpdate(AProjectMixCharacter* character, float deltaTime)
{
	// State dependent logic
	if (character->GetVelocity().Length() > 0)
	{
		//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Green, TEXT("Player velocity is higher than 0"));
		if (ownerInputComp)
		{
			ownerStateMachineComp->SetState(ownerStateMachineComp->RequestState("Run"),PlayerChar);
		}
	}
}

void UIdleState::StateExit(AProjectMixCharacter* character)
{
	// UNBIND all current actions
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, TEXT("Exiting State Idle"));

	

}

void UIdleState::HandleInput(AProjectMixCharacter* character, const FInputActionValue& input)
{
	// State dependent Input
}



