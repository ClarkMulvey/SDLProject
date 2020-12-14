#include <iostream>
#include <cassert>
#include "Vehicle.h"

#ifndef AIRCRAFT_H
#define AIRCRAFT_H

class Aircraft : public Vehicle 
{
private:
	double altitude; 
	double climbBurnRate;

public:
	Aircraft();
	Aircraft(double speed, double fuel, double maxFuel, double accelerateBurnRate, double altitude, double climbBurnRate);
	void GetStatus();
	void Climb(double feet);

	// To help with writing test cases
	const double GetAltitude();

};

// Default Constuctor
Aircraft::Aircraft() {
	this->altitude = 0;
	this->climbBurnRate = 0;
}

// Constructor
Aircraft::Aircraft(double speed, double fuel, double maxFuel, double accelerateBurnRate, double altitude, double climbBurnRate) 
	: Vehicle(speed, fuel, maxFuel, accelerateBurnRate) 
{
	this->altitude = altitude;
	this->climbBurnRate = climbBurnRate;
}

const double Aircraft::GetAltitude() 
{
	return this->altitude;
}

// Print out the current state of the aircraft
void Aircraft::GetStatus() 
{
	std::cout << "The current state of the aircraft: \n";
	std::cout << "Altitude (feet): " << this->altitude << std::endl;
	std::cout << "Speed (mph): " << this->speed << std::endl;
	std::cout << "Fuel (gallons): " << this->fuel << std::endl << std::endl;
}

// Climb a specified number of feet
//    Each additional foot should decrease fuel by 0.01 gallon
//    Signal if there isn't enough fuel to perform the operation
void Aircraft::Climb(double feet)
{
	assert(feet >= 0);

	double fuelSpent = feet * this->climbBurnRate;

	// Aircraft has enough fuel
	if ((this->fuel - fuelSpent) >= 0) 
	{
		this->fuel -= fuelSpent;
		this->altitude += feet;
	}
	// Aircraft does not have enough fuel
	else 
	{
		std::cout << "The aircraft does not have enough fuel for that maneuver.\n\n";
	}
}

//##################### TEST METHODS ############################
void TestAircraftRefuel(Aircraft& aircraft) 
{	
	// ensure no fuel is added if argument is zero
	double currentFuel = aircraft.GetFuel();
	aircraft.Refuel(double(0));
	assert(currentFuel == aircraft.GetFuel());

	// ensure fuel does not exceed maximum allowed fuel
	aircraft.Refuel(aircraft.GetMaxFuel() + double(1.0));
	assert(aircraft.GetFuel() == aircraft.GetMaxFuel());
}

void TestAircraftAccelerate(Aircraft& aircraft) 
{
	// ensure each additional mph decreases fuel by 0.2 gallons
	//    First fill up the tank
	aircraft.Refuel(aircraft.GetMaxFuel());
	double mphIncrease = double(1);
	aircraft.Accelerate(mphIncrease);
	assert(aircraft.GetFuel() == aircraft.GetMaxFuel() - (mphIncrease * 0.2));

	// ensure fuel isn't used if user inputs a too costly acceleration operation
	//    First fill up the tank
	aircraft.Refuel(aircraft.GetMaxFuel());
	//    Find maximum expendable maneuver
	double maxMphIncrease = (aircraft.GetMaxFuel() / 0.2);
	aircraft.Accelerate(maxMphIncrease + double(1));
	//    Ensure no fuel was spent
	assert(aircraft.GetFuel() == aircraft.GetMaxFuel());
}

void TestAircraftClimb(Aircraft& aircraft) 
{
	// ensure each additional foot decreases fuel by 0.01 gallons
	//    First fill up the tank
	aircraft.Refuel(aircraft.GetMaxFuel());
	double altIncrease = double(1);
	aircraft.Climb(altIncrease);
	assert(aircraft.GetFuel() == aircraft.GetMaxFuel() - (altIncrease * 0.01));

	// ensure fuel isn't used if user inputs a too costly climbing operation
	//    First fill up the tank
	aircraft.Refuel(aircraft.GetMaxFuel());
	//    Find maximum expendable maneuver
	double maxAltIncrease = (aircraft.GetMaxFuel() / 0.01);
	aircraft.Climb(maxAltIncrease + double(1));
	//    Ensure no fuel was spent
	assert(aircraft.GetFuel() == aircraft.GetMaxFuel());
}

#endif //AIRFCRAFT_H