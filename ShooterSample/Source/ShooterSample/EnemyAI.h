// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterSampleCharacter.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERSAMPLE_API AEnemyAI : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
private:
	virtual void Tick(float DeltaTime) override;
	
	APawn* PlayerPawn;
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyAIBehaviorTree;
	
public:
	void StartBehaviorTree(AShooterSampleCharacter* Player);
	
	AShooterSampleCharacter* PlayerCharacter;
	AShooterSampleCharacter* MyCharacter;
};
