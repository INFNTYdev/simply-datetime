
#include<iostream>

// Developer Includes:
#include"simplydt/datetime/date/date_interval.hpp"
#include"simplydt/datetime/time/time_interval.hpp"
#include"simplydt/duration/duration_interval.hpp"



// Go back through all code and make sure boundless logic is accounted for
// Need safety checks when adding numbers to make sure they don't hit the ceiling



int main(size_t argc, char* argv[])
{
	//
	DateInterval demo{ DateInterval::DAY, (uint16_t)0 };

	while (!demo.isAtThreshold()) {

		std::cout << demo.toDoubleDigitStr() << std::endl;

		demo.increment();

	}

	return NULL;
}
