// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UObject/UnrealTypePrivate.h"
#include "C_ArchersGameState.generated.h"

DECLARE_EVENT(AC_ArchersGameState, FOnGameStarted);

/**
 * 
 */
UCLASS()
class ARCHERS_API AC_ArchersGameState : public AGameStateBase
{
	GENERATED_BODY()

	AC_ArchersGameState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TArray<APlayerState*> ActivePlayerStates;
	UPROPERTY(EditAnywhere)
	int32 MaxPreparationTime;
	UPROPERTY(ReplicatedUsing=OnRep_CurrentPreparationTimeChanged)
	int32 CurrentPreparationTime;

public:
	int32 GetPlayerStatesAmount() const;
	void AddNewPlayer(const APlayerController* PlayerController);
	
	UFUNCTION(Server,Unreliable)
	void StartGamePreparation();
	
	FOnGameStarted OnGameStarted;

	UFUNCTION()
	void OnRep_CurrentPreparationTimeChanged();
	
};
