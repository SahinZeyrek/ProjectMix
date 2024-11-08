// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseState.h"
#include "StateMachineComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMIX_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateMachineComponent();

	UPROPERTY(VisibleAnywhere)
	UBaseState* CurrentState;


	UPROPERTY(VisibleAnywhere)
	UBaseState* PreviousState;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UBaseState>> ownerStates;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:	

	void SetState(UBaseState* NewState, AProjectMixCharacter* Character);

	void UpdateState(AProjectMixCharacter* Character, float DeltaTime);

	void HandleInput(AProjectMixCharacter* Character, const FInputActionValue& Input);
	
	UBaseState* RequestState(const FString& requestedState);

private:
};
