
#include<iostream>

// Developer Includes:
#include"simplydt/datetime/date/unit/dt_year.hpp"
#include"simplydt/datetime/date/unit/dt_month.hpp"
#include"simplydt/datetime/date/unit/dt_day.hpp"

#include"simplydt/datetime/time/unit/dt_hour.hpp"
#include"simplydt/datetime/time/unit/dt_minute.hpp"
#include"simplydt/datetime/time/unit/dt_second.hpp"
#include"simplydt/datetime/time/unit/dt_millisecond.hpp"

#include"simplydt/common/sequence/linked_sequence.hpp"
#include"simplydt/datetime/sequence/dt_sequence.hpp"



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

using Date = LinkedSequence<uint16_t, Year, Month, Day>;

void dateOut(Date& date)
{
	std::cout << "\nDate: "
		<< date.getInterval(1)->position() << '/'
		<< date.getInterval(2)->position() << '/'
		<< date.getInterval(0)->position();
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

	std::cout << "\n\n\n" << std::endl;

	//
	Date please{ Year(2024), Month(7), Day(2) };

	while (please.getInterval(0)->position() != 2025) {

		dateOut(please);

		please.getInterval(2)->increment(2);

	}

	dateOut(please);

	//
	using DtType = DatetimeSequence<Hour, Minute, Second>::DatetimeType;

	DatetimeSequence<Hour, Minute, Second> omg{
		DtType::TIME_DATETIME,
		Hour(3),
		Minute(54),
		Second(23)
	};

	return NULL;
}
