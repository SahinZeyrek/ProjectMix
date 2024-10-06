// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/BaseState.h"
#include "UObject/NoExportTypes.h"
#include "RunState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMIX_API URunState : public UBaseState
{
	GENERATED_BODY()
public:
	virtual void StateEnter(AProjectMixCharacter* character);

	virtual void StateUpdate(AProjectMixCharacter* character, float deltaTime);

	virtual void StateExit(AProjectMixCharacter* character);

	virtual void HandleInput(AProjectMixCharacter* character, const FInputActionValue& input);

private:


};
