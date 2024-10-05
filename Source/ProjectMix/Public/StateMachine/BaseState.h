// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectMix/ProjectMixCharacter.h"

#include "BaseState.generated.h"
/**
 *  
 */
UCLASS(Blueprintable)
class PROJECTMIX_API UBaseState : public UObject
{
	GENERATED_BODY()
public:

	
	virtual void StateEnter(AProjectMixCharacter* character);

	virtual void StateUpdate(AProjectMixCharacter* character,float deltaTime);

	virtual void StateExit(AProjectMixCharacter* character);

	virtual void HandleInput(AProjectMixCharacter* character, const FInputActionValue& input);

	virtual FString& GetName();

protected:
	UPROPERTY(EditAnywhere)
	FString stateString;


};
