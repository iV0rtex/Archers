// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ArchersGameState.h"
#include "Net/UnrealNetwork.h"

#include "C_ThirdPersonCharacter.h"

AC_ArchersGameState::AC_ArchersGameState()
{
	MaxPreparationTime = 10;
}

void AC_ArchersGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_ArchersGameState, CurrentPreparationTime);
}

void AC_ArchersGameState::BeginPlay()
{
	Super::BeginPlay();

	
}

int32 AC_ArchersGameState::GetPlayerStatesAmount() const
{
	return ActivePlayerStates.Num();	
}

void AC_ArchersGameState::AddNewPlayer(const APlayerController* PlayerController)
{
	
	APlayerState* PlayerState = PlayerController->PlayerState;
	if(PlayerState == nullptr)
	{
		return;
	}
	ActivePlayerStates.Add(PlayerState);
	
}

void AC_ArchersGameState::OnRep_CurrentPreparationTimeChanged()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Turret Has been Destroyed")));
}

void AC_ArchersGameState::StartGamePreparation_Implementation()
{
	CurrentPreparationTime = MaxPreparationTime;
	
}
