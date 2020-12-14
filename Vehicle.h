#include <iostream>
#include <cassert>

#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle 
{
protected:
	double speed;
	double fuel;
	double maxFuel;
	double accelerateBurnRate;

public:
	Vehicle();
	Vehicle(double speed, double fuel, double maxFuel, double accelerateBurnRate);
	void GetStatus();
	void Refuel(double fuel);
	void Accelerate(double mph);

	// To help with writing test cases
	const double getSpeed();
	const double getFuel();
	const double getMaxFuel();
};

// default constructor
Vehicle::Vehicle() 
{
	this->speed = 0;
	this->fuel = 0;
	this->maxFuel = 0;
	this->accelerateBurnRate = 0;
}

// non-default constructor 
Vehicle::Vehicle(double speed, double fuel, double maxFuel, double accelerateBurnRate) 
{
	this->speed = speed;
	this->fuel = fuel;
	this->maxFuel = maxFuel;
	this->accelerateBurnRate = accelerateBurnRate;
}

// GETTERS
const double Vehicle::getSpeed() 
{
	return this->speed;
}

const double Vehicle::getFuel() 
{
	return this->fuel;
}

const double Vehicle::getMaxFuel() 
{
	return this->maxFuel;
}

// Print out the current state of the Vehicle
void Vehicle::GetStatus() 
{
	std::cout << "The current state of the vehicle: \n";
	std::cout << "Speed (mph): " << this->speed << std::endl;
	std::cout << "Fuel (gallons): " << this->fuel << std::endl << std::endl;
}

// Refuel a specified number of gallons
//    You can't overfill the tank
void Vehicle::Refuel(double fuelIntake) 
{
	assert(fuelIntake >= 0);

	if ((this->fuel + fuelIntake) >= this->maxFuel) 
	{
		this->fuel = this->maxFuel;
	}
	else 
	{
		this->fuel += fuelIntake;
	}
}

// Accelerate a specified number of mph
//    Each additional mph should decrease fuel by accelerateBurnRate gallons
//    Signal if there isn't enough fuel to perform the operation
void Vehicle::Accelerate(double mphIncrease) 
{
	assert(mphIncrease >= 0);

	double fuelSpent = mphIncrease * accelerateBurnRate;

	// Vehicle has enough fuel
	if ((this->fuel - fuelSpent) >= 0)
	{
		this->fuel -= fuelSpent;
		this->speed += mphIncrease;
	}
	// Vehicle does not have enough fuel
	else 
	{
		std::cout << "The vehicle does not have enough fuel for that maneuver.\n\n";
	}
}

#endif //VEHICLE_H