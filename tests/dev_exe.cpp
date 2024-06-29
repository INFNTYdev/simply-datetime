
#include<iostream>

// Developer Includes:
#include"simplydt/common/range/int_range.hpp"


// Go back through all code and make sure boundless logic is accounted for
// Need safety checks when adding numbers to make sure they don't hit the ceiling


void rangeTranslateOut(Range<uint32_t>& range, uint32_t units)
{
	//
	Range<uint32_t>::TranslateResult result{
		range.calculateTranslation(
			Range<uint32_t>::POSITIVE,
			units
		)
	};

	std::cout
		<< "\nOrigin: " << range.position()
		<< "\nTranslating +" << units << " units = "
		<< "(" << result.first << " laps, "
		<< "position " << result.second << ")"
		<< "\n\nOUT: " << range
		<< std::endl;
}


int main(size_t argc, char* argv[])
{
	//
	Range<uint32_t> demo{ Range<uint32_t>(1) };

	rangeTranslateOut(demo, 16);

	return NULL;
}
