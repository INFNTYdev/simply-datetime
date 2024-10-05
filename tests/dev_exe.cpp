
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
	uint8_t spacing{ 17 };

	std::cout
		<< "\n--> Datetime Object Analysis <--"
		<< "\n" << std::setw(spacing) << "Datetime: "
		<< dt.datetimeStr(
			Datetime::DateFormat::STANDARD, Datetime::DateLayout::M_D_YYYY,
			Datetime::TimeFormat::STANDARD, Datetime::TimeLayout::H_M_S_P
		)
		<< "\n" << std::setw(spacing) << "Stamp: " << dt
		<< "\n" << std::setw(spacing) << "JDN: " << std::setprecision(16) << dt.toJDN()
		<< "\n" << std::setw(spacing) << "Day of Week: " << dt.dayOfWeek()
		<< "\n" << std::setw(spacing) << "Month: " << dt.monthTitle()
		<< "\n" << std::setw(spacing) << "Days In Month: " << (int)dt.daysInMonth()
		<< "\n" << std::setw(spacing) << "Days In Year: " << dt.daysInYear()
		<< std::endl;
}



int main(size_t argc, char* argv[])
{
	// Simply Datetime r4.v1
	ProjectInfoOut();

	// Project developement time out
	Datetime::TimePoint nowTimePoint{ std::chrono::system_clock::now() };

	Datetime nowSnapshot{ nowTimePoint };

	std::cout
		<< "\n\tToday: " << nowSnapshot.datetimeStr(Datetime::DateFormat::STANDARD)
		<< std::endl;

	// Project start date: June 28th, 2024
	Datetime projInauguration{
		Datetime::Date{ .year = 2024, .month = 6, .day = 28 },
		Datetime::Time{ .hour = 0, .minute = 0, .second = 0 }
	};

	std::cout
		<< "\tElapsed dev time: "
		<< projInauguration.until(nowSnapshot)
		<< std::endl;

	std::cout << "\n\nCONSOLE DEBUG:"
		<< std::endl;

	// DO NOT DELETE ABOVE



	//\\//

	// Start
	Datetime date2{
		Datetime::Date{.year = 2025, .month = 2, .day = 23},
		Datetime::Time{.hour = 19, .minute = 0, .second = 0 }
	};

	dtOut(nowSnapshot);
	dtOut(date2);

	Duration dur{ nowSnapshot.until(date2) };

	std::cout << "\n\nDuration: " << dur << std::endl;

	std::cout << "\n\nChrono: " << Datetime{ nowTimePoint } << std::endl;
	std::cout << "Chrono: " << Datetime{ nowSnapshot.toTimePoint() } << std::endl;

	//\\//



	return NULL;
}
