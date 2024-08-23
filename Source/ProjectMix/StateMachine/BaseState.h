// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectMix/ProjectMixCharacter.h"
/**
 *  
 */
class PROJECTMIX_API BaseState
{
public:
	BaseState();
	virtual ~BaseState();
	virtual void StateEnter(AProjectMixCharacter* character) = 0;
	virtual void StateUpdate(AProjectMixCharacter* character,float deltaTime) = 0;
	virtual void StateExit(AProjectMixCharacter* character) = 0;
	virtual void HandleInput(AProjectMixCharacter* character, const FInputActionValue& input) =0;
};
