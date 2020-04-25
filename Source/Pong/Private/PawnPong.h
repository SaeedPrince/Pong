#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Base class
#include "GameFramework/Pawn.h"

// Interfaces
#include "InterfaceBehaviour.h"

// Generated
#include "PawnPong.generated.h"

UCLASS()
class APawnPong : public APawn , public IInterfaceBehaviour
{
	GENERATED_BODY()

public:

	// Constructor
	APawnPong();

	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		bool IsLeftPong();						// returns true if this instance is the left one otherwise returns false

protected:

	// Interface behaviour start
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Behaviours")
		bool MustReflect();
		virtual bool MustReflect_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Behaviours")
		bool IsVertical();
		virtual bool IsVertical_Implementation() override;
	// Interface behaviour end
	
	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviours")
		bool bReflect;			

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviours")
		bool bVertical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviours")
		bool bLeft;

};
