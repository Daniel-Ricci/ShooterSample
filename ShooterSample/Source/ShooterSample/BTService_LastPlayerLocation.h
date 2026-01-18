// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LastPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERSAMPLE_API UBTService_LastPlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	
	UBTService_LastPlayerLocation();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
