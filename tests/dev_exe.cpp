
#include<iostream>

// Developer Includes:
#include"simplydt/common/range/int_range.hpp"


// Go back through all code and make sure boundless logic is accounted for
// Need safety checks when adding numbers to make sure they don't hit the ceiling


void rangeTranslateOut(Range<uint16_t>& range, uint16_t units)
{
	//
	Range<uint16_t>::TranslateResult result{
		range.calculateTranslation(
			Range<uint16_t>::POSITIVE,
			units
		)
	};

	std::cout
		<< "\nOrigin: " << range.position()
		<< "\nTranslating +" << units << " units = "
		<< "(" << result.first << " laps, "
		<< "position " << result.second << ")"
		<< std::endl;
}


int main(size_t argc, char* argv[])
{
	//
	Range<uint16_t> demo{ Range<uint16_t>(0, 4) };

	rangeTranslateOut(demo, 10);

	return NULL;
}
