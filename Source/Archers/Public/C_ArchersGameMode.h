// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_ArchersGameState.h"
#include "GameFramework/GameModeBase.h"
#include "C_ArchersGameMode.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnPlayerDead);

/**
 * 
 */
UCLASS()
class ARCHERS_API AC_ArchersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	//AC_ArchersGameMode();

protected:
	UPROPERTY()
	AC_ArchersGameState* ArcherGameState;
	AC_ArchersGameState* GetLazyGameState();

	UPROPERTY(EditAnywhere)
	int32 MaxPlayersAmount;

	void GamePreparation();
	void StartGame();

public:
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	UFUNCTION()
	void PlayerDead();
	

	FOnPlayerDead OnPlayerDead;
	
};
