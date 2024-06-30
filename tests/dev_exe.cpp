
#include<iostream>

// Developer Includes:
#include"simplydt/common/interval/interval.hpp"



// Go back through all code and make sure boundless logic is accounted for
// Need safety checks when adding numbers to make sure they don't hit the ceiling



int main(size_t argc, char* argv[])
{
	//
	Interval<uint16_t> milliseconds{ 999 };
	Interval<uint16_t> seconds{ 59 };
	Interval<uint16_t> minutes{ 59 };
	Interval<uint16_t> hours{ 23 };

	milliseconds.linkPrecedingInterval(seconds);
	seconds.linkPrecedingInterval(minutes);
	minutes.linkPrecedingInterval(hours);

	
	//
	while (minutes.position() != 2) {

		std::cout << "\n Time: "
			<< hours << ':' << minutes << ':' << seconds;

		seconds.increment(2);

	}

	return NULL;
}
