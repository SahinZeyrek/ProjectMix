// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectMix/ProjectMixCharacter.h"
#include "Attack/AttackComponent.h"
#include "BaseState.generated.h"
/**
 *  
 */
class UStateMachineComponent;
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
	
	UPROPERTY(VisibleAnywhere)
	AProjectMixCharacter* PlayerChar;

	UPROPERTY(EditAnywhere)
	UEnhancedInputComponent* ownerInputComp;
	
	UPROPERTY()
	UStateMachineComponent* ownerStateMachineComp;

	UPROPERTY()
	UAttackComponent* ownerAttackComponent;

};
