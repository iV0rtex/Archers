// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Arrow.h"

// Sets default values
AC_Arrow::AC_Arrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Arrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

