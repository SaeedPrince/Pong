#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Base class
#include "GameFramework/Actor.h"

// Interfaces
#include "InterfaceBehaviour.h"

// Generated
#include "ActrBorder.generated.h"

UCLASS()
class AActrBorder : public AActor, public IInterfaceBehaviour
{
	GENERATED_BODY()
	
public:	
	
	AActrBorder();

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Behaviours")
		bool MustReflect();
		virtual bool MustReflect_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Behaviours")
		bool IsVertical();
		virtual bool IsVertical_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Behaviours")
		bool IsLeftTeam();
		virtual bool IsLeftTeam_Implementation() override;
	
	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviours")
		bool bReflect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviours")
		bool bVertical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviours")
		bool bLeft;
};
