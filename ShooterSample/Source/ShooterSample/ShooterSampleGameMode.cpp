// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSampleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterSampleCharacter.h"
#include "EnemyAI.h"

AShooterSampleGameMode::AShooterSampleGameMode()
{
	// stub
}

void AShooterSampleGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	AShooterSampleCharacter* Player = Cast<AShooterSampleCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	TArray<AActor*> EnemyAIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAI::StaticClass(), EnemyAIActors);
	
	for(AActor* EnemyAIActor : EnemyAIActors)
	{
		AEnemyAI* EnemyAI = Cast<AEnemyAI>(EnemyAIActor);
		
		if(EnemyAI)
		{
			EnemyAI->StartBehaviorTree(Player);
		}
	}
}
