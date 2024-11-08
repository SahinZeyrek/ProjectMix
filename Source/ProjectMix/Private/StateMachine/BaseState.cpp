// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/BaseState.h"
#include "StateMachine/StateMachineComponent.h"



void UBaseState::StateEnter(AProjectMixCharacter* character)
{
	PlayerChar = character;
	if (ownerInputComp == nullptr)
	{
		ownerInputComp = PlayerChar->GetInputComponent();
	}
	//ownerInputComp->ClearActionBindings();
	if (ownerStateMachineComp == nullptr)
	{
		ownerStateMachineComp = PlayerChar->GetComponentByClass<UStateMachineComponent>();
	}
	if (ownerAttackComponent == nullptr)
	{
		ownerAttackComponent = PlayerChar->GetComponentByClass<UAttackComponent>();
	}
	PlayerChar->BindDefaultActions();
}

void UBaseState::StateUpdate(AProjectMixCharacter* character, float deltaTime)
{
}

void UBaseState::StateExit(AProjectMixCharacter* character)
{
}

void UBaseState::HandleInput(AProjectMixCharacter* character, const FInputActionValue& input)
{
}


FString& UBaseState::GetName()
{
	return stateString;
}

//void UBaseState::Jump()
//{
//	PlayerChar->Jump();
//}
//
//void UBaseState::StopJumping()
//{
//	PlayerChar->StopJumping();
//}
//
//void UBaseState::Move()
//{
//	PlayerChar->Move(PlayerChar->GetInputComponent()->GetBoundActionValue(MoveAction));
//}
//
//void UBaseState::Look()
//{
//	PlayerChar->Look(PlayerChar->GetInputComponent()->GetBoundActionValue(LookAction));
//}
