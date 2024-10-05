// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/RunState.h"
#include "StateMachine/StateMachineComponent.h"

void URunState::StateEnter(AProjectMixCharacter* character)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, TEXT("Entering Run State"));

	// Set up action bindings
	UEnhancedInputComponent* inputComp = character->GetInputComponent();
	inputComp->ClearActionBindings();
	//inputComp->ClearActionValueBindings();
	//inputComp->ClearBindingsForObject(character);

	PlayerChar = character;
	if (inputComp) {

		// Jumping
		inputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &URunState::Jump);
		inputComp->BindAction(JumpAction, ETriggerEvent::Completed, this, &URunState::StopJumping);

		// Moving
		inputComp->BindActionValue(MoveAction);
		inputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &URunState::Move);


		// Looking
		inputComp->BindActionValue(LookAction);
		inputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &URunState::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void URunState::StateUpdate(AProjectMixCharacter* character, float deltaTime)
{
	if (character->GetVelocity().IsNearlyZero(FLT_EPSILON))
	{
		UStateMachineComponent* comp = character->GetComponentByClass<UStateMachineComponent>();
		comp->SetState(comp->RequestState("Idle"), PlayerChar);
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

void URunState::Jump()
{
	PlayerChar->Jump();
}

void URunState::StopJumping()
{
	PlayerChar->StopJumping();
}

void URunState::Move()
{
	PlayerChar->Move(PlayerChar->GetInputComponent()->GetBoundActionValue(MoveAction));
}

void URunState::Look()
{
	PlayerChar->Look(PlayerChar->GetInputComponent()->GetBoundActionValue(LookAction));
}
