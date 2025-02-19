// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/BaseState.h"
#include "UObject/NoExportTypes.h"
#include "AirState.generated.h"

class UAttackComponent;
/**
 * 
 */
UCLASS()
class PROJECTMIX_API UAirState : public UBaseState
{
	GENERATED_BODY()

public:



	virtual void StateEnter(AProjectMixCharacter* character);

	virtual void StateUpdate(AProjectMixCharacter* character, float deltaTime);

	virtual void StateExit(AProjectMixCharacter* character);

	virtual void HandleInput(AProjectMixCharacter* character, const FInputActionValue& input);


	UFUNCTION()
	void ActivateGravity();

	FTimerHandle GravityStartTimer;
	FTimerDelegate GravityStartTimerDelegate;

private:
	UFUNCTION()
	void StopGravity();
	bool bDidAttack;
	UPROPERTY(EditAnywhere)
	float MaxAirTime = 1.5f;
	float CurrentAirTime;
};
