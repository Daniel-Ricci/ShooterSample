// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_PlayerLocationIfSeen.h"
#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AEnemyAI* OwnerController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());
	AShooterSampleCharacter* Player = OwnerController->PlayerCharacter;
	UBlackboardComponent* BlackBoard = OwnerController->GetBlackboardComponent();
	
	if (OwnerController && Player && BlackBoard)
	{
		if(OwnerController->LineOfSightTo(Player))
		{
			BlackBoard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
			OwnerController->SetFocus(Player);
		}
		else
		{
			BlackBoard->ClearValue(GetSelectedBlackboardKey());
			OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}
