// Copyright (c) Astral Games. All right reserved.


#include "Character/DefaultNPC.h"


// Sets default values
ADefaultNPC::ADefaultNPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADefaultNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADefaultNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

