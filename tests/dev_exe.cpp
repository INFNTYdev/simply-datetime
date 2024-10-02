
#include<iostream>


// Library Includes:
#include"simplydt/common/gregorian_calendar/gregorian_util.hpp"




/* /// \\\ /// \\\ /// | TO-DO | \\\ /// \\\ /// \\\ *\
* 
* 10/01/2024
* 
* -> [] N/a.
* 
\* /// \\\ /// \\\ ///  | END |  \\\ /// \\\ /// \\\ */



static void ProjectInfoOut() noexcept
{
	std::cout << '\n'
		<< "\n\tINFINITY Systems, LLC. 2024\n"
		<< "\n\t[ Simply Datetime Library ]"
		<< "\n\tDeveloper executable"
		<< "\n\tRelease: 4 Version: 1"
		<< "\n\t-> (dev_exe.exe)\n"
		<< "\n\tStandard: C++ 20+"
		<< "\n\n" << std::endl;
}



// DEVELOPER DEBUG METHODS



int main(size_t argc, char* argv[])
{
	// Simply Datetime r4.v1
	ProjectInfoOut();

	// Project developement time out

	std::cout << "\n\nCONSOLE DEBUG:"
		<< std::endl;

	// DO NOT DELETE ABOVE



	//\\//

	// Start
	uint16_t nowYear{ 2024 };
	uint8_t nowMonth{ 10 };
	uint8_t nowDay{ 1 };

	std::cout << (int)GregorianCalendar::interpretJDNDay(2460584.5) << std::endl;

	//\\//



	return NULL;
}
