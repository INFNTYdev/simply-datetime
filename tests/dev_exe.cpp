
#include<iostream>


// Library Includes:
#include"simplydt/datetime/datetime.hpp"




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

void dtOut(const Datetime& dt) noexcept
{
	std::cout
		<< "\n--> Datetime Object Analysis <--"
		<< "\n\tMonth: " << dt.monthTitle()
		<< " (" << (int)dt.month() << ")"
		<< "\n\tYear: " << dt.year()
		<< std::endl;
}



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
	Datetime demo{};

	dtOut(demo);

	//\\//



	return NULL;
}
