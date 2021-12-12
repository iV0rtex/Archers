// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "I_Hittable.h"
#include "GameFramework/Character.h"
#include "C_ThirdPersonCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartOverdraw);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireAction);

UCLASS()
class ARCHERS_API AC_ThirdPersonCharacter : public ACharacter, public IHittableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_ThirdPersonCharacter();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(Replicated)
	bool bIsDead;
	UPROPERTY(Replicated)
	bool bOnOverdraw;
	UPROPERTY(Replicated)
	bool bOnTargeting;
	UPROPERTY(Replicated)
	bool bReadyToFire;
	UPROPERTY(Replicated)
	bool bCanMove;
	
	UPROPERTY(EditAnywhere)
	float DodgeChance;
	UPROPERTY(EditAnywhere)
	float DefaultOverdrawSpeed;
	UPROPERTY(EditAnywhere)
	float MaxArraySpeed;
	UPROPERTY(EditAnywhere)
	float MaxDamage;
	UPROPERTY(EditAnywhere)
	float AtkSpeedUpdater;
	
	float GatheringPowerTime;
	float GatheringPowerMinTime;
	float GatheringPowerTimeLeft;
	

	FTimerHandle GatheringPowerTimeHandle;

	UFUNCTION()
	bool IsHit() const;
	
	UFUNCTION(Server,Reliable)
	void Die();

	UFUNCTION(Server,Unreliable)
	void GatheringPower();
	UFUNCTION(Server,Unreliable)
	void EndGatheringPower();

	UFUNCTION(Server,Unreliable,BlueprintCallable)
	void StopOverdrawServer();
	UFUNCTION(Server,Unreliable,BlueprintCallable)
	void StartOverdrawServer();
	UFUNCTION(Server,Unreliable,BlueprintCallable)
	void StartTargeting();
	UFUNCTION(Server,Unreliable,BlueprintCallable)
	void StopTargeting();
	UFUNCTION(Server,Unreliable,BlueprintCallable)
	void Fire();
	UFUNCTION(Server,Unreliable,BlueprintCallable)
	void FireDone();
	UFUNCTION(NetMulticast,Unreliable)
	void ShowArrow();
	UFUNCTION(NetMulticast,Unreliable)
	void HideArrow();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent * BowStaticMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent * BowArrowStaticMesh;
	

public:
	UPROPERTY(BlueprintAssignable)
	FOnDead OnDead;

	UPROPERTY(BlueprintAssignable)
	FOnStartOverdraw OnStartOverdraw;

	UPROPERTY(BlueprintAssignable)
	FOnFireAction OnFireAction;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server,Reliable,BlueprintCallable,WithValidation)
	virtual void TryToHit() override;
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetPawnIsDead();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetCanMove();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetDefaultOverdrawSpeed();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetOnTarget();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UStaticMeshComponent* GetBowArrowStaticMesh();
	
	UFUNCTION(BlueprintCallable,BlueprintPure) //TODO: Remove  when all be done
	float GetGatheringPowerTime();
	UFUNCTION(BlueprintCallable,BlueprintPure) //TODO: Remove when all be done
	float GetGatheringPowerTimeLeft();
	UFUNCTION(BlueprintCallable,BlueprintPure) //TODO: Remove when all be done
	float GetMaxArraySpeed();
	UFUNCTION(BlueprintCallable,BlueprintPure) //TODO: Remove when all be done
	float GetMaxDamage();
	
	/////TODO: Move to Helper
	UFUNCTION(BlueprintCallable)
	float CalculateDamage(float PowerTime, float PowerTimeLeft, float MDamage);
	UFUNCTION(BlueprintCallable)
	float CalculateSpeed(float PowerTime, float PowerTimeLeft, float MSpeed);

};
