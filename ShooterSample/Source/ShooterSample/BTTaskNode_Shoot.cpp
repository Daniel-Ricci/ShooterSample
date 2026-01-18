// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskNode_Shoot.h"
#include "EnemyAI.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("Shoot At Player");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AEnemyAI* OwnerController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());
	if (OwnerController)
	{
		AShooterSampleCharacter* OwnerCharacter = OwnerController->MyCharacter;
		AShooterSampleCharacter* PlayerCharacter = OwnerController->PlayerCharacter;
		
		if (OwnerCharacter && PlayerCharacter && PlayerCharacter->IsAlive())
		{
			OwnerCharacter->DoShoot();
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
