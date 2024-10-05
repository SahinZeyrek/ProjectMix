// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack/AttackComponent.h"
#include "ProjectMix/ProjectMixCharacter.h"
// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	AProjectMixCharacter* owner = Cast<AProjectMixCharacter>(GetOwner());
	OwnerAnimInstance = owner->GetMesh()->GetAnimInstance();
	auto input = owner->GetInputComponent();
	if (input)
	{
		input->BindAction(AttackAction, ETriggerEvent::Started, this, &UAttackComponent::Attack);
	}
	// ...
	
}


void UAttackComponent::Attack()
{
	if (bReceiveInput && bCanAttack)
	{
		OwnerAnimInstance->Montage_Play(AttackString[CurrentAttackCounter]);
	}
	++CurrentAttackCounter;
	if (CurrentAttackCounter > (AttackString.Num() - 1))
	{
		CurrentAttackCounter = 0;
	}
	
}

void UAttackComponent::AltAttack()
{
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

