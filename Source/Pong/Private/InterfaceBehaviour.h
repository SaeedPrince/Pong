#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceBehaviour.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceBehaviour : public UInterface
{
	GENERATED_BODY()
};

class IInterfaceBehaviour
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Behaviours")	// returns true if it should reflect the ball than scoring
		bool MustReflect();						

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Behaviours")	// returns true if its shape is vertical than horizontal
		bool IsVertical();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Behaviours") // returns true if it belongs to left team rather than the right team
		bool IsLeftTeam();

};
