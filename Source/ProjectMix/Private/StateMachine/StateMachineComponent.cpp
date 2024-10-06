// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/StateMachineComponent.h"

// Sets default values for this component's properties
UStateMachineComponent::UStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateState(Cast<AProjectMixCharacter>(GetOwner()),DeltaTime);
	// ...
}

void UStateMachineComponent::SetState(UBaseState* NewState, AProjectMixCharacter* Character)
{
	if (CurrentState)
	{
		CurrentState->StateExit(Character);
	}
	PreviousState = CurrentState;
	CurrentState = NewState;

	if (CurrentState)
	{
		CurrentState->StateEnter(Character);
	}
}

void UStateMachineComponent::UpdateState(AProjectMixCharacter* Character, float DeltaTime)
{
	if (CurrentState)
	{
		CurrentState->StateUpdate(Character, DeltaTime);
	}
}

void UStateMachineComponent::HandleInput(AProjectMixCharacter* Character, const FInputActionValue& Input)
{
	if (CurrentState)
	{
		CurrentState->HandleInput(Character, Input);
	}
}

UBaseState* UStateMachineComponent::RequestState(const FString& requestedState)
{
	for (TSubclassOf<UBaseState> state : Cast<AProjectMixCharacter>(GetOwner())->GetStates())
	{
		FString* name = &state.GetDefaultObject()->GetName();
		if (*name == requestedState)
		{
			return Cast<UBaseState>(state->GetDefaultObject());
		}
	}
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, TEXT("REQUESTED STATE NOT FOUND"));

	return nullptr;
}

