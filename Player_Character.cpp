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


#include "Player_Character.h"

// Sets default values
APlayer_Character::APlayer_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating a scene component to attach the FPS arm
	FPS_ARM_scene = CreateDefaultSubobject<USceneComponent>(TEXT("ROTATION_SCENE"));
	FPS_ARM_scene->AttachTo(RootComponent);

	//Creating a First Person Arm.
	FPS_ARM = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("fps_arms"));
	FPS_ARM->AttachTo(FPS_ARM_scene);

}

// Called when the game starts or when spawned
void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
	


	
}

// Called every frame
void APlayer_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Walk_speed();

	

	//Calling Ray cast function if we can rotate -- Good for performance
	if (Can_rotate && Can_rotate_global)
	{
		T_RayCast();
		T_Normalized();
	}

	
	

}

// Called to bind functionality to input
void APlayer_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Axis
	PlayerInputComponent->BindAxis("MOVING_Vert", this, &APlayer_Character::Move_ver);
	PlayerInputComponent->BindAxis("MOVING_HORZ", this, &APlayer_Character::Move_Her);

	PlayerInputComponent->BindAxis("MouseX", this, &APlayer_Character::Look_X);
	PlayerInputComponent->BindAxis("MouseY", this, &APlayer_Character::Look_Y);

	PlayerInputComponent->BindAxis("Shift", this, &APlayer_Character::Shift_func);


	//Action
	PlayerInputComponent->BindKey(INTERACT, IE_Pressed, this, &APlayer_Character::Interaction_Func);
	PlayerInputComponent->BindKey(Use, IE_Pressed, this, &APlayer_Character::Use_Func);

}

void APlayer_Character::Move_ver(float Axis)
{
	//Moving Forward and Backward Funcation

	//Checking whether we can move or not.
	if (Can_rotate && Can_rotate_global)
	{


		if (Axis)
		{
			//Making Player Move either forward or backward.
			AddMovementInput(GetActorForwardVector(), Axis);

		}


		/*
			Axis == 1 MovingForward
			Axis == 0 Not Moving
			Axis = -1 MovingBackward
		*/

		if (Axis >= 1)
		{
			IsFORWARD_INPUT = true;
			IsBACKWARD_INPUT = false;
		}
		else if (Axis <= -1)
		{
			IsBACKWARD_INPUT = true;
			IsFORWARD_INPUT = false;
		}
		else if (Axis == 0)
		{
			IsBACKWARD_INPUT = false;
			IsFORWARD_INPUT = false;
		}
	}
	else
	{
		IsBACKWARD_INPUT = false;
		IsFORWARD_INPUT = false;
	}
}

void APlayer_Character::Move_Her(float Axis)
{
	if (Can_rotate && Can_rotate_global)
	{

		//Making Player Move either left or right.
		if (Axis)
		{
			AddMovementInput(GetActorRightVector(), Axis);
		}

		/*
			Axis == 1 MovingRight
			Axis == 0 Not Moving
			Axis = -1 MovingLeft
		*/

		if (Axis >= 1)
		{
			IsRIGHT_INPUT = true;
			IsLEFT_INPUT = false;
		}
		else if (Axis <= -1)
		{
			IsLEFT_INPUT = true;
			IsRIGHT_INPUT = false;
		}
		else if (Axis == 0)
		{
			IsLEFT_INPUT = false;
			IsRIGHT_INPUT = false;
		}
	}
	else
	{
		IsLEFT_INPUT = false;
		IsRIGHT_INPUT = false;
	}
}

void APlayer_Character::Look_X(float Axis)
{
	Turn_Soeed = Axis;

	//Checking whether we can Rotate or not.
	if (Can_rotate && Can_rotate_global)
	{
		if (Axis)
		{
			//Rotating Player Character via Yaw axis
			AddActorLocalRotation(FRotator(0, Axis, 0));
		}
	}
}

void APlayer_Character::Look_Y(float Axis)
{
	Mouse_Y_speed = Axis;
	if (Can_rotate && Can_rotate_global)
	{
		if (Axis)
		{
			float Temp = FPS_ARM_scene->GetRelativeRotation().Pitch + Axis;


			if (Temp > -90 && Temp < 60)
			{
				//Rotating FPS scene compoenent via Pitch Axis
				FPS_ARM_scene->AddLocalRotation(FRotator(Axis, 0, 0));

				/*HandR->AddLocalOffset(FVector((-data / 9), 0, 0));
				HandL->AddLocalOffset(FVector((-data / 9), 0, 0));*/
			}

		}
	}
}

void APlayer_Character::Interaction_Func()
{
	// Checking if Hit_Box is not NULL
	if (Hit_Box)
	{
		Hit_Box->b_Hit = true;
	}
}

void APlayer_Character::Use_Func()
{
}

void APlayer_Character::Shift_func(float Axis)
{
	/*
		Axis > 0: Player is holding shift
		Axis <= 0: Player is not holding shift
	*/
	if (Axis > 0)
	{
		IsRUN_INPUT = true;
	}
	else if (Axis <= 0)
	{
		IsRUN_INPUT = false;
	}
}


void APlayer_Character::Walk_speed()
{
	/*							ABOUT
		This function adjusts the player's speed based on current input.
		For example, it checks if the player pressed 'W'. If so, the player's
		speed will gradually increase to 300 using the Math::FInterpTo() function.

		There are a few other variables being used, such as:

		Allow_Sprint - Determines whether the player can run
		Sprint_Time - Used to prevent the player from running continuously after a certain period
	*/
	if ((IsFORWARD_INPUT || IsBACKWARD_INPUT) && !Sprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, 300, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 4);

	}


	if ((!IsFORWARD_INPUT && !IsBACKWARD_INPUT) && (IsLEFT_INPUT || IsRIGHT_INPUT) && !Sprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = 100;
	}

	if (!IsFORWARD_INPUT && !IsBACKWARD_INPUT && !IsLEFT_INPUT && !IsRIGHT_INPUT && !Sprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = 0;
	}



	// Checking if forward input (W) and run input (Shift) are being held
	// If both are held, check if allow_sprint is true; if so, speed will increase
	if (IsFORWARD_INPUT && IsRUN_INPUT && Allow_sprint)
	{
		/*						HOW DOES IT WORK?
				We use a temporary variable called 'x' and normalize it so that:
				- If Sprint_Time is 0, the output will be 300
				- If Sprint_Time is 120, the output will be 800



				𝑓(𝑆𝑝𝑟𝑖𝑛𝑔𝑇𝑖𝑚𝑒) = 𝑀∈𝑆𝑝𝑒𝑒𝑑 + (𝑆𝑝𝑟𝑖𝑛𝑔𝑇𝑖𝑚𝑒 / 120) ⋅ (𝑀𝑎𝑥𝑆𝑝𝑒𝑒𝑑 − 𝑀∈𝑆𝑝𝑒𝑒𝑑)
	
				


				This means that as the player continues running, their speed gradually decreases for added realism.

				You can remove this feature if desired.

				NOTE: 120 is the maximum sprint time.
					  If you want to extend the sprint duration,
					  replace 120 with your desired maximum value.


					  

		*/


		float x = 300 + (Sprint_Time / 120) * (800 - 300);


		/*
			Check if sprint time is greater than 20
			If so, set running speed to 800
			If not, set running speed to 'x' to gradually reduce speed
		*/
		if (Sprint_Time > 20)
		{
			GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, 800, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 4);
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, x, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 1);
		}




		/*
			Check if sprint time is greater than 0
			If so, gradually reduce sprint time
			If not, stop the player from running by setting allow_sprint to false
		*/
		if (Sprint_Time > 0)
		{
			Sprint_Time = Sprint_Time - (GetWorld()->DeltaTimeSeconds * 9);
		}
		else if (Sprint_Time <= 0)
		{
			Allow_sprint = false;
		}
		Sprint = true;
	}
	else if ((!IsFORWARD_INPUT || !IsRUN_INPUT) || !Allow_sprint)
	{
		//Gradually increasing sprint_time
		if (Sprint_Time < 120)
		{
			Sprint_Time += 10 * GetWorld()->GetDeltaSeconds();
		}

	}

	if ((!IsFORWARD_INPUT || !IsRUN_INPUT) || !Allow_sprint)
	{
		Sprint = false;
	}

	// Check if sprint time is greater than 50
	// If so, set allow_sprint to true
	if (Sprint_Time > 50)
	{
		if (!Allow_sprint)
		{
			Allow_sprint = true;
		}
	}
}

void APlayer_Character::T_RayCast()
{
	/*								HOW DOES IT WORK?
				This function creates a raycast to check if it hits any objects.
				If it hits something, we can use the object that was hit for further tasks.

				We use the Hit_Box class frequently here. This class is useful for selecting objects
				or performing tasks like turning lights on/off, among others.
				This can be achieved by hitting the Hit_Box class, which allows us to change
				a variable called Hit to true.
				From there, we can execute tasks through the class itself.

				NOTE : THE BEST WAY TO EXECUTE TASKS IN Hit_Box is to create a blueprint class

	*/


	FHitResult Hit;
	FVector StartTrace = Camera_Component->GetComponentLocation();
	FVector ForwardVector = Camera_Component->GetForwardVector();
	FVector EndTrace = ((ForwardVector * Ray_Distance) + StartTrace);


	FCollisionQueryParams Query;
	Query.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, Query))
	{


		if (Hit.GetComponent()->GetAttachmentRoot() != NULL)
		{
			if (Hit.GetActor()->GetClass()->IsChildOf<AHit_Box>())
			{
				Hit_Box = Cast<AHit_Box>(Hit.GetActor());
				if (Hit_Box)
				{
					Hit_Box->Being_Look_at = true;
				}
			}
			else
			{
				if (Hit_Box)
				{
					Hit_Box->Being_Look_at = false;
					Hit_Box = NULL;
				}
			}


			if (Hit_Box)
			{
				if (Pre_Box)
				{
					if (Hit_Box != Pre_Box)
					{
						Pre_Box->Being_Look_at = false;
						Pre_Box = Hit_Box;
					}
				}
				else
				{
					Pre_Box = Hit_Box;
				}
			}


		}





	}

	if (!Hit.bBlockingHit)
	{
		if (Hit_Box)
		{
			Hit_Box->Being_Look_at = false;
			Hit_Box = NULL;
		}
	}

}

void APlayer_Character::T_Sway_Func(float DeltaSecond)
{

	/*float MaxSwayDegreeYaw = 10;
	float MaxSwayDegreePitch = 10;
	
	

	float FinalYaw;
	float InsRotY = 0;

	float FinalPitch;
	float InsRotPitch = 0;


	FinalYaw = Turn_Soeed * 2;
	Anim_Yaw_Sway = FMath::Clamp(FMath::FInterpTo(Anim_Yaw_Sway, FinalYaw + InsRotY, DeltaSecond, 2.5), MaxSwayDegreeYaw * -1, MaxSwayDegreeYaw);
	FinalPitch = Mouse_Y_speed * 2;
	Anim_Pitch_Sway = FMath::Clamp(FMath::FInterpTo(Anim_Pitch_Sway, FinalPitch + InsRotPitch, DeltaSecond, 2.5), MaxSwayDegreePitch * -1, MaxSwayDegreePitch);*/

	/*USE THIS CODE IF YOU WANNA SWAY MOVEMENT FOR YOUR CHARACTER ARM*/
	
}

void APlayer_Character::T_Normalized()
{
}
