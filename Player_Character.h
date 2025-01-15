// MIT License
//
// Copyright (c) 2024 GameDevRichtofen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Hit_Box.h"
#include "Engine.h"
#include "Player_Character.generated.h"

UCLASS()
class RADAR_API APlayer_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	//Generals
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool Can_rotate_global = true;// it is variable that can stop player from moving and rotating but only other classes are eligble to change it
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = "Variables")
		bool Can_rotate = true; //it is variable that can either allow/stop player from moving and rotating but only this class is eligble to modified it.

	//Moving forward and backward variables
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool IsFORWARD_INPUT;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool IsBACKWARD_INPUT;

	//Moving Left and right variables
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool IsLEFT_INPUT;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool IsRIGHT_INPUT;

	//Necessary input for running, EXAMPLE : Left Shif
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool IsRUN_INPUT;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool Sprint;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool Allow_sprint;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		float Sprint_Time;

	//Inputs
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Inputs")
		FKey TURN_ON;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Inputs")
		FKey INTERACT;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Inputs")
		FKey SWITCHING;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Inputs")
		FKey Use;

	//Mehses
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Inputs")
		USkeletalMeshComponent* FPS_ARM;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Inputs")
		USceneComponent* FPS_ARM_scene;


	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Inputs")
		UCameraComponent* Camera_Component;

	

	//Turing speed for various usage
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		float Turn_Soeed;


	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		float Mouse_Y_speed;

	//Ray Cast Distance 
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		float Ray_Distance = 200;


	
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		float Anim_Yaw_Sway = 0;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		float Anim_Pitch_Sway = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actors")
		AHit_Box* Hit_Box;

	AHit_Box* Pre_Box;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool Setting_up;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool Using_Radar;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Variables")
		bool Using_Gun;

private:

	//Variables associated with movement and rotation.
	void Move_ver(float Axis);
	void Move_Her(float Axis);

	void Look_X(float Axis);
	void Look_Y(float Axis);



	//Interaction funcation for interacting with avalible objects
	void Interaction_Func();


	//Use Objects
	void Use_Func();


	void Shift_func(float Axis);

	void Walk_speed();

	//T funcations are the funcation that being called every frame through Tick funcation
	void T_RayCast();


	void T_Sway_Func(float DeltaSecond);

	//Normalize every variable inside this funcation
	void T_Normalized();

};
