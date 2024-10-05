// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "EnhancedInputComponent.h"
#include "AttackComponent.generated.h"
class AProjectMixCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMIX_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

	void Attack();
	void AltAttack();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Attack String")
	TArray<UAnimMontage*> AttackString;

	UFUNCTION()
	void SetCanAttack(bool canAttack = true) { bCanAttack = canAttack; }
	UFUNCTION()
	void SetReceiveInput(bool receiveInput = true) { bReceiveInput = receiveInput; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	uint8 CurrentAttackCounter;

	//used to receive input at all
	bool bReceiveInput = true;
	// used to determine when player can attack again
	bool bCanAttack = true;

	UAnimInstance* OwnerAnimInstance;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;
};
