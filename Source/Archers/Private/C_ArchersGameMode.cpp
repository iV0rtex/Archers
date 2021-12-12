// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ArchersGameMode.h"

#include "C_ThirdPersonCharacter.h"

/*
AC_ArchersGameMode::AC_ArchersGameMode()
{
	
	MaxPlayersAmount = 2;
}
*/

AC_ArchersGameState* AC_ArchersGameMode::GetLazyGameState()
{
	if(ArcherGameState == nullptr)
	{
		AGameStateBase* GameS = GameState;
		if(IsValid(GameS))
		{
			ArcherGameState = Cast<AC_ArchersGameState>(GameS);
		}
	}
	return ArcherGameState;
	
}

void AC_ArchersGameMode::GamePreparation()
{
	GetLazyGameState()->StartGamePreparation();
	GetLazyGameState()->OnGameStarted.AddUFunction(this,"StartGame");
	
}

void AC_ArchersGameMode::StartGame()
{
	
}

void AC_ArchersGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	/*AC_ArchersGameState* GameS = GetLazyGameState();
	if(!IsValid(GameS))
	{
		return;
	}

	APawn* Pawn = NewPlayer->GetPawn();
	AC_ThirdPersonCharacter* ArcherPawn = Cast<AC_ThirdPersonCharacter>(Pawn);
	if(!IsValid(ArcherPawn))
	{
		return;
	}
	
	GameS->AddNewPlayer(NewPlayer);
	
	OnPlayerDead.BindDynamic(this,&AC_ArchersGameMode::PlayerDead);
	ArcherPawn->OnDead.Add(OnPlayerDead);
	
	if(GameS->GetPlayerStatesAmount() >= MaxPlayersAmount)
	{
		GamePreparation();
	}*/
	
}

void AC_ArchersGameMode::PlayerDead()
{
	
}
