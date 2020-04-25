#include "PawnBall.h"
#include "Kismet/KismetMathLibrary.h"
#include "InterfaceBehaviour.h"

APawnBall::APawnBall()
{
	PrimaryActorTick.bCanEverTick = false;
	bCanCollide = true;
	MoveFrequency = 0.02f;
	ScaleValue = 0.001f;
	ResetTime = 0.1f;
}

FTimerHandle APawnBall::GetMovementTimer()
{
	return TimerMove;
}

void APawnBall::StartGame()
{
	Direction = FVector(UKismetMathLibrary::RandomFloatInRange(-160.0f, 160.0f), UKismetMathLibrary::RandomFloatInRange(-160.0f, 160.0f), 0.0f);
	GetWorld()->GetTimerManager().SetTimer(TimerMove, this, &APawnBall::MoveBall, MoveFrequency, true);
}

void APawnBall::MoveBall()
{
	APawn::AddMovementInput(Direction, ScaleValue);
}

void APawnBall::BallStartCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCanCollide)
	{
		AActor* Overlapped = _SolveOverlap(OtherActor, SweepResult);
		if (IsValid(Overlapped))
		{
			IInterfaceBehaviour* theInterface = Cast<IInterfaceBehaviour>(Overlapped);	// Cast to see if the actor implements the interface
			if (theInterface)
			{
				if (IInterfaceBehaviour::Execute_MustReflect(Overlapped))
				{
					if (IInterfaceBehaviour::Execute_IsVertical(Overlapped))
					{
						Direction = FVector(Direction.X, UKismetMathLibrary::Multiply_FloatFloat(Direction.Y, -1.0f), 0.0f);
					}
					else
					{
						Direction = FVector(UKismetMathLibrary::Multiply_FloatFloat(Direction.X, -1.0f) ,Direction.Y, 0.0f);
					}
				}
				else
				{
					if (IInterfaceBehaviour::Execute_IsLeftTeam(Overlapped))
					{
						OnBallScored.Broadcast(true);
					}
					else
					{
						OnBallScored.Broadcast(false);
					}
				}
				bCanCollide = false;
				FTimerHandle TimerReset;
				GetWorld()->GetTimerManager().SetTimer(TimerReset, this, &APawnBall::ResetCollision, ResetTime);
			}
		}
	}
}

void APawnBall::ResetCollision()
{
	bCanCollide = true;
}

AActor* APawnBall::_SolveOverlap(AActor* OtherActor, const FHitResult& HitResult)
{
	AActor* retActor = nullptr;
	if (IsValid(OtherActor))
	{
		AActor* HitActor = HitResult.GetActor();
		if (IsValid(HitActor))
		{
			if (HitActor == this)	// Test hit actor with our class is the key
			{
				retActor = OtherActor;
			}
			else
			{
				retActor = HitActor;
			}
		}
	}
	return retActor;
}