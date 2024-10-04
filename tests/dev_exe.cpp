
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
	uint8_t spacing{ 16 };

	std::cout
		<< "\n--> Datetime Object Analysis <--"
		<< "\n" << std::setw(spacing) << "Year: " << dt.year()
		<< "\n" << std::setw(spacing) << "Month: " << dt.monthTitle()
		<< "\n" << std::setw(spacing) << "Day of Week: " << dt.dayOfWeek()
		<< "\n" << std::setw(spacing) << "Datetime: " << dt
		<< "\n" << std::setw(spacing) << "JDN: " << std::setprecision(16) << dt.toJDN()
		<< "\n" << std::setw(spacing) << "Attributes: "
		<< "\n" << std::setw(spacing) << "\t-> Year = " << (int)dt.year()
		<< ", Month = " << (int)dt.month()
		<< ", Day = " << (int)dt.day()
		<< "\n" << std::setw(spacing) << "\t-> Hour = " << (int)dt.hour()
		<< ", Minute = " << (int)dt.minute()
		<< ", Second = " << (int)dt.second()
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
	Datetime date1{
		Datetime::Date{.year = 2024, .month = 10, .day = 3},
		Datetime::Time{.hour = 17, .minute = 54, .second = 0 }
	};

	Datetime date2{
		std::chrono::system_clock::now()
	};

	dtOut(date1);
	dtOut(date2);

	Duration dur{ date1.until(date2) };

	std::cout << "\nDuration: " << dur << std::endl;

	date1 += dur;

	dtOut(date1);

	//\\//



	return NULL;
}
