
#include<iostream>

// Developer Includes:
#include"simplydt/datetime/date/date_interval.hpp"
#include"simplydt/datetime/time/time_interval.hpp"
#include"simplydt/duration/duration_interval.hpp"

#include"simplydt/datetime/date/unit/dt_year.hpp"
#include"simplydt/datetime/date/unit/dt_month.hpp"
#include"simplydt/datetime/date/unit/dt_day.hpp"



// Go back through all code and make sure boundless logic is accounted for
// Need safety checks when adding numbers to make sure they don't hit the ceiling



int main(size_t argc, char* argv[])
{
	//
	Day day{ 1 };
	Month month{ 7 };
	Year year{ 2024 };

	day.linkPrecedingInterval(month);
	month.linkPrecedingInterval(year);

	while (year.position() != 2025) {

		if (day.isAtStart()) {
			std::cout << "\n\n" << month.getName();
		}

		std::cout << "\nDate: "
			<< month.toDoubleDigitStr() << '/'
			<< day.toDoubleDigitStr() << '/'
			<< year << " | " << day.getDayOfWeek();

		day.increment();

	}

	return NULL;
}
