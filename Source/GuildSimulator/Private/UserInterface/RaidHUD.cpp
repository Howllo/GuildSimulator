// Copyright (c) Astral Games. All right reserved.


#include "UserInterface/RaidHUD.h"
#include "Character/DefaultCharacterAI.h"
#include "Character/RaidPlayerCharacter.h"
#include "GameMisc/RaidGameMode.h"
#include "Kismet/GameplayStatics.h"

void ARaidHUD::BeginPlay()
{
	GameMode = Cast<ARaidGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GetRaidPlayer = Cast<ARaidPlayerCharacter>(GameMode->DefaultPawnClass.GetDefaultObject());
}

void ARaidHUD::DrawHUD()
{
	if(bStartSelecting)
	{
		if(FoundActors.Num() > 0)
		{
			for(int32 i = 0; i < FoundActors.Num(); i++)
			{
				FoundActors[i]->CharacterNotSelected();
			}
		}

		//Check if Current Select is not null to reset it.
		if(GetRaidPlayer)
		{
			if(GetRaidPlayer->CurrentSelectedCharacter != nullptr)
			{
				GetRaidPlayer->CurrentSelectedCharacter->CharacterNotSelected();
				GetRaidPlayer->CurrentSelectedCharacter = nullptr;
			}
		}

		FoundActors.Empty();
		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(255,255,255,0.15f), FirstPoint.X, FirstPoint.Y, CurrentPoint.X - FirstPoint.X,
				CurrentPoint.Y - FirstPoint.Y);

		float const DistanceBetweenTwoPoints = FMath::Sqrt(FMath::Square(CurrentPoint.X - FirstPoint.X) + FMath::Square(CurrentPoint.Y - FirstPoint.Y));

		//If the distance between points is less than 2 than select a single NPC.
		if(DistanceBetweenTwoPoints < 3.0f || FirstPoint == CurrentPoint)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if(PlayerController)
			{
				FHitResult Hit;
				PlayerController->GetHitResultUnderCursor(ECC_Pawn,true, Hit);

				if(GetRaidPlayer && Hit.GetActor()->GetClass()->IsChildOf(ADefaultCharacterAI::StaticClass()))
				{
					FoundActors.Add(Cast<ADefaultCharacterAI>(Hit.GetActor()));
					GetRaidPlayer->CurrentSelectedCharacter = Cast<ADefaultCharacterAI>(Hit.GetActor());
					if(GetRaidPlayer->CurrentSelectedCharacter != nullptr)
					{
						GetRaidPlayer->CurrentSelectedCharacter->CharacterSelected();
					} else
					{
						UE_LOG(LogTemp,Warning, TEXT("GetPlayerDefault CurrentSleeectionCharacter is nullptr."))
					}
				}
			}
		}
		else
		{
			GetActorsInSelectionRectangle<ADefaultCharacterAI>(FirstPoint,CurrentPoint, FoundActors, false, true);

			if(FoundActors.Num() > 0)
			{
				for(int32 i = 0; i < FoundActors.Num(); i++)
				{
					FoundActors[i]->CharacterSelected();
				}
			}
		}
	}
}

FVector2D ARaidHUD::GetMousePos2D() const
{
	float PosX = 0;
	float PosY = 0;
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);
	return FVector2D(PosX, PosY);
}
