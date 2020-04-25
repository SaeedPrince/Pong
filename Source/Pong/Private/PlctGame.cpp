#include "PlctGame.h"
#include "PawnBall.h"
#include "PawnPong.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

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