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
				This function creates a raycast to check if it hits any objects.
				If it hits something, we can use the object that was hit for further tasks.

				We use the Hit_Box class frequently here. This class is useful for selecting objects
				or performing tasks like turning lights on/off, among others.
				This can be achieved by hitting the Hit_Box class, which allows us to change
				a variable called Hit to true.
				From there, we can execute tasks through the class itself.

				NOTE : THE BEST WAY TO EXECUTE TASKS IN Hit_Box is to create a blueprint class

*/


#include "Hit_Box.h"

// Sets default values
AHit_Box::AHit_Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHit_Box::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHit_Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

