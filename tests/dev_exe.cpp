
#include<iostream>

// Developer Includes:
#include"simplydt/datetime/date/unit/dt_year.hpp"
#include"simplydt/datetime/date/unit/dt_month.hpp"
#include"simplydt/datetime/date/unit/dt_day.hpp"

#include"simplydt/datetime/time/unit/dt_hour.hpp"
#include"simplydt/datetime/time/unit/dt_minute.hpp"
#include"simplydt/datetime/time/unit/dt_second.hpp"
#include"simplydt/datetime/time/unit/dt_millisecond.hpp"



// Go back through all code and make sure boundless logic is accounted for
// Need safety checks when adding numbers to make sure they don't hit the ceiling



void datetimeOut(Year& year, Month& month, Day& day, Hour& hr, Minute& min, Second& sec)
{
	std::cout << "\nDatetime: "
		<< day.getDayOfWeek() << ", "
		<< month.toDoubleDigitStr() << '/'
		<< day.toDoubleDigitStr() << '/'
		<< year << ' '
		<< hr.toDoubleDigitStr() << ':'
		<< min.toDoubleDigitStr() << ':'
		<< sec.toDoubleDigitStr()
		<< ' ' << hr.getPhaseStr();
}


int main(size_t argc, char* argv[])
{
	//
	Year year{ 2024 };
	Month month{ 7 };
	Day day{ 1 };

	Hour hour{ 10 };
	Minute minute{ 15 };
	Second second{ 23 };
	Millisecond ms{ NULL };

	ms.linkPrecedingInterval(second);
	second.linkPrecedingInterval(minute);
	minute.linkPrecedingInterval(hour);
	hour.linkPrecedingInterval(day);
	day.linkPrecedingInterval(month);
	month.linkPrecedingInterval(year);

	//

	while (hour.position() != 15) {

		datetimeOut(year, month, day, hour, minute, second);

		minute.increment(5);

	}

	return NULL;
}
