// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachine/BaseState.h"
#include "IdleState.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTMIX_API UIdleState : public UBaseState
{
	GENERATED_BODY()

public:

	virtual void StateEnter(AProjectMixCharacter* character);

	virtual void StateUpdate(AProjectMixCharacter* character, float deltaTime);

	virtual void StateExit(AProjectMixCharacter* character);

	virtual void HandleInput(AProjectMixCharacter* character, const FInputActionValue& input);


private:
	

	// STATE DEPENDENT FUNCTIONS
	
};
