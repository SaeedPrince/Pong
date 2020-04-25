#include "PlctGame.h"
#include "PawnBall.h"
#include "PawnPong.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

APlctGame::APlctGame()
{
	/**********************************************
	Initializing variables inside the constructor
	**********************************************/
	LeftScore = 0;
	RightScore = 0;
	ControllerMaxX = 120.0f;
	ControllerMinX = -120.0f;
	ControllerSpeed = 10.0f;
	RestartTime = 0.1f;
	BallLocation = FVector(0.0f, 0.0f, 40.0f);
}

int32 APlctGame::GetScore(bool bLeft)
{
	return (bLeft ? LeftScore : RightScore);
}

void APlctGame::BeginPlay()
{
	
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	/******************
	Finding map objects
	*******************/
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnBall::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		BallRef = Cast<APawnBall>(FoundActors[0]);
		if (IsValid(BallRef))
		{
			BallRef->OnBallScored.AddDynamic(this, &APlctGame::Goal);
			BallRef->StartGame();
		}
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnPong::StaticClass(), FoundActors);
	for (AActor* anyActor : FoundActors)
	{
		APawnPong* pwnPong = Cast<APawnPong>(anyActor);
		if (IsValid(pwnPong))
		{
			(pwnPong->IsLeftPong()) ? (LeftPongRef = pwnPong) : (RightPongRef = pwnPong);
		}
	}
	// Create widget to show the scores
	if (IsValid(WidgetBP))
	{
		UUserWidget* widgetRef = CreateWidget<UUserWidget>(this, WidgetBP);
		if (IsValid(widgetRef))
		{
			widgetRef->AddToViewport(0);
		}
	}
}

void APlctGame::Goal(bool bLeft)
{
	bLeft ? LeftScore++ : RightScore++;
	if (IsValid(BallRef))
	{
		FTimerHandle tim = BallRef->GetMovementTimer();
		UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, tim);
		UPawnMovementComponent* MovementComp = BallRef->GetMovementComponent();
		if (IsValid(MovementComp))
		{
			MovementComp->StopMovementImmediately();
			FTimerHandle TimerRestart;
			GetWorld()->GetTimerManager().SetTimer(TimerRestart, this, &APlctGame::RestartGame, RestartTime);
		}
	}
}

void APlctGame::RestartGame()
{
	if (IsValid(BallRef))
	{
		BallRef->SetActorLocation(BallLocation);
		BallRef->StartGame();
	}
}

void APlctGame::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Axis mapping
	InputComponent->BindAxis("LeftControl", this, &APlctGame::LeftControlAxis);
	InputComponent->BindAxis("RightControl", this, &APlctGame::RightControlAxis);
}

void APlctGame::LeftControlAxis(float inAxisValue)
{
	if (IsValid(LeftPongRef))
	{
		_HandleInput(LeftPongRef, inAxisValue);
	}
}

void APlctGame::RightControlAxis(float inAxisValue)
{
	if (IsValid(RightPongRef))
	{
		_HandleInput(RightPongRef, inAxisValue);
	}
}

void APlctGame::_HandleInput(APawnPong* inPong, float inAxisValue)
{
	FVector plnLoc = inPong->GetActorLocation();
	float mve = inAxisValue * ControllerSpeed + plnLoc.X;
	if (mve < ControllerMaxX && mve > ControllerMinX)
	{
		inPong->SetActorLocation(FVector(mve, plnLoc.Y, plnLoc.Z));
	}
}