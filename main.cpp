

#include <iostream>
#include "Vehicle.h"
#include "Aircraft.h"
#include "Automobile.h"


int main()
{
    Aircraft artemis1(double(10000), double(17000), double(15000), double(735000));

    TestAircraftRefuel(artemis1);
    TestAircraftAccelerate(artemis1);
    TestAircraftClimb(artemis1);
}
