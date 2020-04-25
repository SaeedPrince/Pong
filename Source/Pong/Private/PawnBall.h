#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Base class
#include "GameFramework/Pawn.h"

// Generated
#include "PawnBall.generated.h"

class AActor;
class UPrimitiveComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBallScored, bool, inLeft);

UCLASS()
class APawnBall : public APawn
{
	GENERATED_BODY()

public:
	// Constructor
	APawnBall();

	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		FTimerHandle GetMovementTimer();		// Player controller requires this handle to stop movement at score

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Events")
		void StartGame();						// Starts ball movement from center

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Ball")
		FBallScored OnBallScored;

protected:

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Events")
		void MoveBall();						// Moves the ball toward direction

	UFUNCTION(BlueprintCallable, Category = "Events")	// Calls when ball collides with something
		void BallStartCollision(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Events")	// Calls to reset collision
		void ResetCollision();

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball")
		bool bCanCollide;			// We want collision only once, so we use this flag

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball")
		float MoveFrequency;		// Saves ball movement frequency

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball")
		float ResetTime;			// Collision rest time

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball")
		float ScaleValue;			// Saves ball movement value

	UPROPERTY(BlueprintReadWrite, Category = "Ball")
		FTimerHandle TimerMove;			// Timer handle to control ball movement

	UPROPERTY(BlueprintReadWrite, Category = "Ball")
		FVector Direction;			// Saves ball direction

private:

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Calculations", meta = (AllowPrivateAccess = "true"))		// When we have an overlap event, we need to distinguish overlapped actor
		class AActor*_SolveOverlap(class AActor* OtherActor, const FHitResult& HitResult);
};
