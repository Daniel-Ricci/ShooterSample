// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_LastPlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_LastPlayerLocation::UBTService_LastPlayerLocation()
{
	NodeName = TEXT("Update Player Last Known Location");
}

void UBTService_LastPlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	
	if (PlayerPawn && BlackBoard)
	{
		BlackBoard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
}
