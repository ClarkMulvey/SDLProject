#include <iostream>
#include <cassert>

#ifndef AIRCRAFT_H
#define AIRCRAFT_H

class Aircraft {
private:
	double alt;
	double speed;
	double fuel;
	double maxFuel;

public:
	Aircraft();
	Aircraft(double alt, double speed, double fuel, double maxFuel);
	void GetStatus();
	void Refuel(double fuel);
	void Accelerate(double mph);
	void Climb(double feet);

	// To help with writing test cases
	const double getAlt();
	const double getSpeed();
	const double getFuel();
	const double getMaxFuel();

};

// Default Constuctor
Aircraft::Aircraft() {
	this->alt = 0;
	this->speed = 0;
	this->fuel = 0;
	this->maxFuel = 0;
}

// Constructor
Aircraft::Aircraft(double alt, double speed, double fuel, double maxFuel) {
	this->alt = alt;
	this->speed = speed;
	this->fuel = fuel;
	this->maxFuel = maxFuel;
}

const double Aircraft::getAlt() {
	return this->alt;
}

const double Aircraft::getSpeed() {
	return this->speed;
}

const double Aircraft::getFuel() {
	return this->fuel;
}

const double Aircraft::getMaxFuel() {
	return this->maxFuel;
}

// Print out the current state of the aircraft
void Aircraft::GetStatus() {

	std::cout << "The current state of the aircraft: \n";
	std::cout << "Altitude (feet): " << this->alt << std::endl;
	std::cout << "Speed (mph): " << this->speed << std::endl;
	std::cout << "Fuel (gallons): " << this->fuel << std::endl << std::endl;
}

// Refuel a specified number of gallons
//    You can't overfill the tank
void Aircraft::Refuel(double fuel) {

	assert(fuel >= 0);

	if ((this->fuel + fuel) >= this->maxFuel) {
		this->fuel = this->maxFuel;
	}
	else {
		this->fuel += fuel;
	}
}

// Accelerate a specified number of mph
//    Each additional mph should decrease fuel by 0.2 gallon
//    Signal if there isn't enough fuel to perform the operation
void Aircraft::Accelerate(double mph) {

	assert(mph >= 0);

	double fuelSpent = mph * 0.2;

	// Aircraft has enough fuel
	if ((this->fuel - fuelSpent) >= 0) {
		this->fuel -= fuelSpent;
		this->speed += mph;
	}
	// Aircraft does not have enough fuel
	else {
		std::cout << "The aircraft does not have enough fuel for that maneuver.\n\n";
	}
}

// Climb a specified number of feet
//    Each additional foot should decrease fuel by 0.01 gallon
//    Signal if there isn't enough fuel to perform the operation
void Aircraft::Climb(double feet) {

	assert(feet >= 0);

	double fuelSpent = feet * 0.01;

	// Aircraft has enough fuel
	if ((this->fuel - fuelSpent) >= 0) {
		this->fuel -= fuelSpent;
		this->alt += feet;
	}
	// Aircraft does not have enough fuel
	else {
		std::cout << "The aircraft does not have enough fuel for that maneuver.\n\n";
	}
}

//##################### TEST METHODS ############################
void TestAircraftRefuel(Aircraft& aircraft) {
	
	// ensure no fuel is added if argument is zero
	double currentFuel = aircraft.getFuel();
	aircraft.Refuel(double(0));
	assert(currentFuel == aircraft.getFuel());

	// ensure fuel does not exceed maximum allowed fuel
	aircraft.Refuel(aircraft.getMaxFuel() + double(1.0));
	assert(aircraft.getFuel() == aircraft.getMaxFuel());

}

void TestAircraftAccelerate(Aircraft& aircraft) {

	// ensure each additional mph decreases fuel by 0.2 gallons
	//    First fill up the tank
	aircraft.Refuel(aircraft.getMaxFuel());
	double mphIncrease = double(1);
	aircraft.Accelerate(mphIncrease);
	assert(aircraft.getFuel() == aircraft.getMaxFuel() - (mphIncrease * 0.2));

	// ensure fuel isn't used if user inputs a too costly acceleration operation
	//    First fill up the tank
	aircraft.Refuel(aircraft.getMaxFuel());
	//    Find maximum expendable maneuver
	double maxMphIncrease = (aircraft.getMaxFuel() / 0.2);
	aircraft.Accelerate(maxMphIncrease + double(1));
	//    Ensure no fuel was spent
	assert(aircraft.getFuel() == aircraft.getMaxFuel());

}

void TestAircraftClimb(Aircraft& aircraft) {

	// ensure each additional foot decreases fuel by 0.01 gallons
	//    First fill up the tank
	aircraft.Refuel(aircraft.getMaxFuel());
	double altIncrease = double(1);
	aircraft.Climb(altIncrease);
	assert(aircraft.getFuel() == aircraft.getMaxFuel() - (altIncrease * 0.01));

	// ensure fuel isn't used if user inputs a too costly climbing operation
	//    First fill up the tank
	aircraft.Refuel(aircraft.getMaxFuel());
	//    Find maximum expendable maneuver
	double maxAltIncrease = (aircraft.getMaxFuel() / 0.01);
	aircraft.Climb(maxAltIncrease + double(1));
	//    Ensure no fuel was spent
	assert(aircraft.getFuel() == aircraft.getMaxFuel());

}

#endif //AIRFCRAFT_H