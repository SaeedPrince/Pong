#include "PawnPong.h"

APawnPong::APawnPong()
{
	PrimaryActorTick.bCanEverTick = false;
	bReflect = false;
	bVertical = false;
	bLeft = false;

}

bool APawnPong::IsLeftPong()
{
	return bLeft;
}

bool APawnPong::MustReflect_Implementation()
{
	return bReflect;
}

bool APawnPong::IsVertical_Implementation()
{
	return bVertical;
}