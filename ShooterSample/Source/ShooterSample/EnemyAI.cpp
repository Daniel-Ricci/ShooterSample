// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAI::StartBehaviorTree(AShooterSampleCharacter* Player)
{
	if (EnemyAIBehaviorTree)
	{
		MyCharacter = Cast<AShooterSampleCharacter>(GetPawn());
		
		if (Player)
		{
			PlayerCharacter = Player;
		}
		
		RunBehaviorTree(EnemyAIBehaviorTree);
		
		GetBlackboardComponent()->SetValueAsVector("StartLocation", MyCharacter->GetActorLocation());
	}
}
