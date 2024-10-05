// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/BaseState.h"



void UBaseState::StateEnter(AProjectMixCharacter* character)
{
	//StateEnterBlueprint(character);
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
