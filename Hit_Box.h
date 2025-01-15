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


/*								HOW DOES IT WORK?
				Hit_box class is a useful class for an interaction process

				This class is useful for selecting objects
				or performing tasks like turning lights on/off, among others.
				This can be achieved by hitting the Hit_Box class, which allows us to change
				a variable called Hit to true.
				From there, we can execute tasks through the class itself.

				NOTE : THE BEST WAY TO EXECUTE TASKS IN Hit_Box is to create a blueprint class
				
				IMPORTANT : Make sure to add a box, capsul, sphere... collision to this class either
				for C++ or BP.

*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hit_Box.generated.h"

UCLASS()
class RADAR_API AHit_Box : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHit_Box();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public :

	//Being look at is a variable that can be used when player is looking at Hit_box class, this can be done via Ray casting.
	/*                  Example : 
	        
			void AHit_Box::Tick(float DeltaTime)
			{
			    [FUNCTION NAME]()
			}

			void AHit_Box::[FUNCTION NAME]()
			{
			     if(Being_Look_at)
				 {
				     Execute Task here
				 }
			}
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool Being_Look_at;


	//Hit variable is a variable that can be used to interact with the Hit_box class, this can be done via Ray cast.
	/*                  Example :

			void AHit_Box::Tick(float DeltaTime)
			{
				[FUNCTION NAME]()
			}

			void AHit_Box::[FUNCTION NAME]()
			{
				 if(b_Hit)
				 {
					 Execute Task here
					 b_Hit = false;--if you don't want to destroy the class after execution make sure to turn off b_Hit to stop repeating the same code.
				 }
			}
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool b_Hit;

};
