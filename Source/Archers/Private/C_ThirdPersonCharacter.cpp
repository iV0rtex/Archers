// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ThirdPersonCharacter.h"

#include "C_Arrow.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AC_ThirdPersonCharacter::AC_ThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsDead = false;
	bOnOverdraw = false;
	bOnTargeting = false;
	bReadyToFire = true;
	bCanMove = true;
	DodgeChance = 65.f;
	DefaultOverdrawSpeed= 1.f;
	MaxArraySpeed= 5000.f;
	MaxDamage = 500.f;
	AtkSpeedUpdater = 1;
	GatheringPowerTime = 0.1;
	GatheringPowerMinTime = 0.1;
	GatheringPowerTimeLeft = 0.f;

	BowStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));
	BowArrowStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowArrow"));
	
	BowStaticMesh->SetupAttachment(GetMesh(),TEXT("hand_l"));
	BowArrowStaticMesh->SetupAttachment(GetMesh(),TEXT("hand_r"));
	BowArrowStaticMesh->SetVisibility(false,false);
	BowArrowStaticMesh->SetIsReplicated(true);
	
}

void AC_ThirdPersonCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_ThirdPersonCharacter, bIsDead);
	DOREPLIFETIME(AC_ThirdPersonCharacter, bOnOverdraw);
	DOREPLIFETIME(AC_ThirdPersonCharacter, bOnTargeting);
	DOREPLIFETIME(AC_ThirdPersonCharacter, bReadyToFire);
	DOREPLIFETIME(AC_ThirdPersonCharacter, bCanMove);
}

// Called when the game starts or when spawned
void AC_ThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AC_ThirdPersonCharacter::IsHit() const
{
	return FMath::RandRange(0,100) > DodgeChance;
	
}

void AC_ThirdPersonCharacter::Die_Implementation()
{
	bIsDead = true;
	if(OnDead.IsBound())
	{
		OnDead.Broadcast();
	}
}

void AC_ThirdPersonCharacter::GatheringPower_Implementation()
{
	UAnimMontage* Montage = GetCurrentMontage();
	GatheringPowerTime = GatheringPowerTimeLeft = Montage->GetPlayLength()/ AtkSpeedUpdater;
	if(GatheringPowerTime < GatheringPowerMinTime)
	{
		GatheringPowerTime = GatheringPowerTimeLeft = GatheringPowerMinTime;
	}

	GetWorld()->GetTimerManager().SetTimer(GatheringPowerTimeHandle,this,&AC_ThirdPersonCharacter::EndGatheringPower,GatheringPowerTime);
}

void AC_ThirdPersonCharacter::EndGatheringPower_Implementation()
{
	if(GetWorldTimerManager().IsTimerActive(GatheringPowerTimeHandle))
	{
		GatheringPowerTimeLeft = GetWorldTimerManager().GetTimerRemaining(GatheringPowerTimeHandle);
		GetWorldTimerManager().ClearTimer(GatheringPowerTimeHandle);
	}
}

void AC_ThirdPersonCharacter::StopOverdrawServer_Implementation()
{
	EndGatheringPower();
	bOnOverdraw = false;
}


void AC_ThirdPersonCharacter::StartOverdrawServer_Implementation()
{
	if(!bOnTargeting)
	{
		return;
	}

	bOnOverdraw = true;
	
	if(!bReadyToFire)
	{
		return;
	}
	
	OnStartOverdraw.Broadcast();

	GatheringPower();
}

void AC_ThirdPersonCharacter::StartTargeting_Implementation()
{
	bOnTargeting = true;
	bCanMove = false;
	ShowArrow();
}

void AC_ThirdPersonCharacter::StopTargeting_Implementation()
{
	bOnTargeting = false;
	bCanMove = true;
	bReadyToFire = true;
	bOnOverdraw = false;
	HideArrow();
}

void AC_ThirdPersonCharacter::Fire_Implementation()
{
	if(!bOnTargeting || !bReadyToFire)
	{
		return;
	}
	bReadyToFire = false;
	HideArrow();
	OnFireAction.Broadcast(); //TODO: Rewrite to C++. Fast decision
	//
	//TODO: 
	//CLear time left when onFire event is removed
	//AC_Arrow * NewArrow = GetWorld()->SpawnActor<AC_Arrow>(BowArrowStaticMesh->GetComponentTransform().GetLocation(),BowArrowStaticMesh->GetComponentTransform().Rotator());
	
}

void AC_ThirdPersonCharacter::FireDone_Implementation()
{
	bReadyToFire = true;
	if(!bOnTargeting)
	{
		return;
	}
	ShowArrow();
	if(!bOnOverdraw)
	{
		return;
	}
	StartOverdrawServer();
}

void AC_ThirdPersonCharacter::HideArrow_Implementation()
{
	BowArrowStaticMesh->SetVisibility(false,false);
	
}

void AC_ThirdPersonCharacter::ShowArrow_Implementation()
{
	BowArrowStaticMesh->SetVisibility(true,false);
}

// Called every frame
void AC_ThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_ThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AC_ThirdPersonCharacter::GetPawnIsDead()
{
	return bIsDead;
}

bool AC_ThirdPersonCharacter::GetCanMove()
{
	return bCanMove;
}

float AC_ThirdPersonCharacter::GetDefaultOverdrawSpeed()
{
	return DefaultOverdrawSpeed;
}

bool AC_ThirdPersonCharacter::GetOnTarget()
{
	return bOnTargeting;
}

float AC_ThirdPersonCharacter::GetGatheringPowerTime()
{
	return GatheringPowerTime;
}

float AC_ThirdPersonCharacter::GetGatheringPowerTimeLeft()
{
	return GatheringPowerTimeLeft;
}

float AC_ThirdPersonCharacter::GetMaxArraySpeed()
{
	return MaxArraySpeed;
}

float AC_ThirdPersonCharacter::GetMaxDamage()
{
	return MaxDamage;
}

UStaticMeshComponent* AC_ThirdPersonCharacter::GetBowArrowStaticMesh()
{
	return BowArrowStaticMesh;
}

float AC_ThirdPersonCharacter::CalculateDamage(float PowerTime, float PowerTimeLeft, float MDamage)
{
	 return MDamage * FMath::Abs(PowerTimeLeft/PowerTime - 1);
}

float AC_ThirdPersonCharacter::CalculateSpeed(float PowerTime, float PowerTimeLeft, float MSpeed)
{
	return -1 * (MSpeed * FMath::Abs(PowerTimeLeft/PowerTime - 1));
}

void AC_ThirdPersonCharacter::TryToHit_Implementation()
{
	Die();
}

bool AC_ThirdPersonCharacter::TryToHit_Validate()
{
	return !bIsDead && IsHit();
}

