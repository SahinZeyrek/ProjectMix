// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/RunState.h"
#include "StateMachine/StateMachineComponent.h"

void URunState::StateEnter(AProjectMixCharacter* character)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, TEXT("Entering Run State"));

	UBaseState::StateEnter(character);

}

void URunState::StateUpdate(AProjectMixCharacter* character, float deltaTime)
{
	if (character->GetVelocity().IsNearlyZero(FLT_EPSILON))
	{
		ownerStateMachineComp->SetState(ownerStateMachineComp->RequestState("Idle"), PlayerChar);
	}
}

void URunState::StateExit(AProjectMixCharacter* character)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, TEXT("Exiting Run State"));
	UEnhancedInputComponent* inputComp = character->GetInputComponent();

}

void URunState::HandleInput(AProjectMixCharacter* character, const FInputActionValue& input)
{
}

