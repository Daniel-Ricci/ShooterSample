// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterSampleGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AShooterSampleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AShooterSampleGameMode();
	
protected:
	virtual void BeginPlay() override;
};



