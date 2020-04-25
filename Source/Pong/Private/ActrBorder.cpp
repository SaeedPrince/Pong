#include "ActrBorder.h"

AActrBorder::AActrBorder()
{
	PrimaryActorTick.bCanEverTick = false;
	bReflect = false;
	bVertical = false;

}

bool AActrBorder::MustReflect_Implementation()
{
	return bReflect;
}

bool AActrBorder::IsVertical_Implementation()
{
	return bVertical;
}

bool AActrBorder::IsLeftTeam_Implementation()
{
	return bLeft;
}
