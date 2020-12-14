#include <iostream>
#include "Vehicle.h"
#include "Aircraft.h"
#include "Automobile.h"


int main()
{
    Aircraft artemis1(double(17000), double(15000), double(735000), double(0.2), double(20000), double(0.01));

    // Test the Aircraft methods - if there are no assert failures they all pass
    TestAircraftRefuel(artemis1);
    TestAircraftAccelerate(artemis1);
    TestAircraftClimb(artemis1);

    Automobile getawayCar(double(120), double(10), double(12), double(0.125), "white");

    // Test the Automobile methods - if there are no assert failures they all pass
    TestAutomobileRefuel(getawayCar);
    TestAutomobileAccelerate(getawayCar);
    TestAutomobileChangeColor(getawayCar);
}
