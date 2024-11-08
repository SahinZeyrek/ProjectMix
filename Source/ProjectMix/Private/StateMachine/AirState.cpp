// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/AirState.h"
#include "StateMachine/StateMachineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectMix/ProjectMixCharacter.h"

void UAirState::StateEnter(AProjectMixCharacter* character)
{
	UBaseState::StateEnter(character);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Entering Air State"));
	//ownerAttackComponent = PlayerChar->GetComponentByClass<UAttackComponent>();
	if (ownerAttackComponent)
	{
		ownerAttackComponent->BindAttackAction();
		ownerAttackComponent->OnAttackDelegate.AddUniqueDynamic(this, &UAirState::StopGravity);

		ownerAttackComponent->EnterAerialMode();
	}
}

void UAirState::StateUpdate(AProjectMixCharacter* character, float deltaTime)
{
	if (!PlayerChar->GetCharacterMovement()->IsFalling())
	{
		ownerStateMachineComp->SetState(ownerStateMachineComp->RequestState("Run"), PlayerChar);
	}
	if (bDidAttack)
	{
		CurrentAirTime += deltaTime;
		if (CurrentAirTime > MaxAirTime)
		{
			CurrentAirTime = 0;
			bDidAttack = false;
			ActivateGravity();
		}
	}
}

void UAirState::StateExit(AProjectMixCharacter* character)
{
	ActivateGravity();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Exiting Air State"));
	if (ownerAttackComponent)
	{
		ownerAttackComponent->UnbindAttackAction();

		ownerAttackComponent->ExitAerialMode();
	}
}

void UAirState::HandleInput(AProjectMixCharacter* character, const FInputActionValue& input)
{

}

void UAirState::StopGravity()
{
	// Disable gravity
	PlayerChar->GetCharacterMovement()->GravityScale = 0.0f;

	// Stop vertical movement (Z-axis)
	FVector CurrentVelocity = PlayerChar->GetCharacterMovement()->Velocity;
	CurrentVelocity.Z = 0.0f;  // Set the vertical velocity to 0 to prevent floating
	PlayerChar->GetCharacterMovement()->Velocity = CurrentVelocity;

	bDidAttack = true;
	//GravityStartTimerDelegate.BindUFunction(this, FName("ActivateGravity"));
	//GetWorld()->GetTimerManager().SetTimer(GravityStartTimer, GravityStartTimerDelegate, 1.f, false);
	//GetWorld()->GetTimerManager().ClearTimer(GravityStartTimer);

	//GetWorld()->GetTimerManager().SetTimer(GravityStartTimer, this, &UAirState::ActivateGravity, 2.f, false);

}

void UAirState::ActivateGravity()
{
	PlayerChar->GetCharacterMovement()->GravityScale = 1.75f;
}
