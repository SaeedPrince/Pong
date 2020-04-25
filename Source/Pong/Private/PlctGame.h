#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Base class
#include "GameFramework/PlayerController.h"

// Generated
#include "PlctGame.generated.h"

class APawnBall;
class APawnPong;
class UUserWidget;

UCLASS()
class APlctGame : public APlayerController
{
	GENERATED_BODY()
	
public:

	// Constructor
	APlctGame();

	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		int32 GetScore(bool bLeft);						// Widget uses this function for showing the scores

protected:

	// Functions
	virtual void BeginPlay() override;					// Runs at runtime fist and once
	virtual void SetupInputComponent() override;		// Assign input

	UFUNCTION(BlueprintCallable, Category = "Input")	// Handles left controller
		void LeftControlAxis(float inAxisValue);

	UFUNCTION(BlueprintCallable, Category = "Input")	// Handles right controller
		void RightControlAxis(float inAxisValue);

	// Properties
	UPROPERTY(BlueprintReadWrite, Category = "Score")
		int32 LeftScore;				// Saves left player score

	UPROPERTY(BlueprintReadWrite, Category = "Score")
		int32 RightScore;				// Saves right player score

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizations")
		float ControllerMaxX;			// Saves controller maximum X in case it moves

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizations")
		float ControllerMinX;			// Saves controller minimum X in case it moves

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizations")
		float ControllerSpeed;			// Saves right player score

	UPROPERTY(BlueprintReadWrite, Category = "Score")
		FVector BallLocation;			// Saves initial ball location

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects")
		class APawnBall* BallRef;		// Saves ball reference

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects")
		class APawnPong* LeftPongRef;	// Saves left controller reference

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects")
		class APawnPong* RightPongRef;	// Saves right controller reference

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> WidgetBP;

private:

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Input Handling", meta = (AllowPrivateAccess = "true"))		// 
		void _HandleInput(class APawnPong* inPong, float inAxisValue);

};
