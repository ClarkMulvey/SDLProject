#include <iostream>
#include <cassert>
#include "Vehicle.h"

#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

// This unrealistic automobile has the ability to change colors
//   This is of course to get away from the cops if needed,
//   This color changing mechanism will take half a tank of fuel to change 
//   The automobile's color
class Automobile : public Vehicle
{
private:
	std::string color;

public:
	Automobile();
	Automobile(double speed, double fuel, double maxFuel, double accelerateBurnRate, std::string color);
	void GetStatus();
	void Brake(double seconds);
	void ChangeColor(std::string color);

	// To help with writing test cases
	const std::string GetColor();
};

// Default Constuctor
Automobile::Automobile() {
	this->color = "black";
}

// Constructor
Automobile::Automobile(double speed, double fuel, double maxFuel, double accelerateBurnRate, std::string color)
	: Vehicle(speed, fuel, maxFuel, accelerateBurnRate)
{
	this->color = color;
}

// Get methods to help with tests
const std::string Automobile::GetColor()
{
	return this->color;
}

// Print out the current state of the aircraft
void Automobile::GetStatus()
{
	std::cout << "The current state of the automobile: \n";
	std::cout << "Color: " << this->color << std::endl;
	std::cout << "Speed (mph): " << this->speed << std::endl;
	std::cout << "Fuel (gallons): " << this->fuel << std::endl << std::endl;
}

// Brake the Car
//   Each second of braking will decrease the speed of the Automobile by 5 mph
void Automobile::Brake(double seconds)
{
	assert(seconds >= 0);

	double mphDecrease = seconds * 5;

	if (this->speed - mphDecrease <= 0)
	{
		this->speed = 0;
	}
	else
	{
		this->speed - mphDecrease;
	}
}

// Change the color of the car to get away from Cops
//   This will consume half of the total fuel tank volume
//   Signal if there isn't enough fuel to perform this opeartion
//   We are going to assume that any string can be classified as a 
//   viable color
//   In addition, if the input is the same color that the car already has,
//   Let the driver know and doen't consume any fuel
void Automobile::ChangeColor(std::string color)
{
	if (this->color == color)
	{
		std::cout << "The automobile already is that color.\n\n";
	}
	else if (this->fuel >= (this->maxFuel / 2))
	{
		this->fuel -= (this->maxFuel / 2);
		this->color = color;
	}
	else
	{
		std::cout << "The automobile does not have enough fuel to change color.\n\n";
	}
}

//##################### TEST METHODS ############################
void TestAutomobileRefuel(Automobile& automobile)
{
	// ensure no fuel is added if argument is zero
	double currentFuel = automobile.GetFuel();
	automobile.Refuel(double(0));
	assert(currentFuel == automobile.GetFuel());

	// ensure fuel does not exceed maximum allowed fuel
	automobile.Refuel(automobile.GetMaxFuel() + double(1.0));
	assert(automobile.GetFuel() == automobile.GetMaxFuel());
}

void TestAutomobileAccelerate(Automobile& automobile)
{
	// ensure each additional mph decreases fuel by 0.125 gallons
	//    First fill up the tank
	automobile.Refuel(automobile.GetMaxFuel());
	double mphIncrease = double(1);
	automobile.Accelerate(mphIncrease);
	assert(automobile.GetFuel() == automobile.GetMaxFuel() - (mphIncrease * 0.125));

	// ensure fuel isn't used if user inputs a too costly acceleration operation
	//    First fill up the tank
	automobile.Refuel(automobile.GetMaxFuel());
	//    Find maximum expendable maneuver
	double maxMphIncrease = (automobile.GetMaxFuel() / 0.125);
	automobile.Accelerate(maxMphIncrease + double(1));
	//    Ensure no fuel was spent
	assert(automobile.GetFuel() == automobile.GetMaxFuel());
}

void TestAutomobileChangeColor(Automobile& automobile)
{
	// test to make sure if the same color it doesn't drain fule and doesn't change the color
	// First fill up the tank
	automobile.Refuel(automobile.GetMaxFuel());
	// get the color of the automobile
	std::string currentColor = automobile.GetColor();
	//attempt to change the color
	automobile.ChangeColor(currentColor);

	assert(automobile.GetFuel() == automobile.GetMaxFuel());

	// test to make sure the fuel is drained by half of the tank if the color is changed
	// also assert the color has changed
	// Change color of the automobile
	currentColor == "black" ? automobile.ChangeColor("red") : automobile.ChangeColor("black");

	assert(automobile.GetFuel() == (automobile.GetMaxFuel() / 2.0) && automobile.GetColor() != currentColor);

}

#endif //AUTOMOBILE_H