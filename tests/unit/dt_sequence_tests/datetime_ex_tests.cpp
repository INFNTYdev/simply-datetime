
#include<gtest/gtest.h>
#include<iostream>
#include<string>

#include"simplydt/datetime/comp/virtual/vdatetime_ex.hpp"


// Julian Day Number integrity tests
namespace VDatetimeExJDNTests {

	// These tests are designed to ensure the VDatetimeEx class
	// appropriately handles JDN's to maintain accuracy.


	const inline double MIN_JDN{ 2'440'587.5 };// January 1, 1970 00:00:00:000
	const inline double MAX_JDN{ 25'657'226.49999999 };// December 31, 65534 23:59:59:999

	const uint32_t REPR_COUNT{ 23'216'638 };// Quantity of representable dates


	void msgOut(const std::string& msg) noexcept
	{
		std::cout << std::setw(13)
			<< "[ TEST MSG ] "
			<< std::setprecision(17)
			<< msg;
	}

	void failOut(const std::string& msg) noexcept
	{
		std::cout << '\n' << std::setw(13)
			<< "[ FAILURE! ] "
			<< std::setprecision(17)
			<< msg;
	}

	template <typename T>
	void fpOut(const std::string& label, const T& val) noexcept
	{
		std::cout << '\n' << std::setprecision(17)
			<< "\t\t -> "
			<< label << ": "
			<< std::setprecision(17)
			<< val;
	}

	
	// Tests if VDatetimeEx class produces accurate JDN values
	TEST(VDtExJDNIntegrityTests, DateJDNCalculationTest)
	{
		// Designated test sample
		VDatetimeEx sample{};

		uint16_t epochYear{ 1970 };
		uint16_t epochMonth{ 1 };
		uint16_t epochDay{ 1 };

		// Confirm correct default date
		if (sample.year() != epochYear) {
			failOut("Invalid epoch year provided by sample");
			fpOut("Year expected", epochYear);
			fpOut("Year given", sample.year());
			std::cout << std::endl;
			FAIL();
		}

		if (sample.month() != epochMonth) {
			failOut("Invalid epoch month provided by sample");
			fpOut("Month expected", epochMonth);
			fpOut("Month given", sample.month());
			std::cout << std::endl;
			FAIL();
		}

		if (sample.day() != epochDay) {
			failOut("Invalid epoch day provided by sample");
			fpOut("Day expected", epochDay);
			fpOut("Day given", sample.day());
			std::cout << std::endl;
			FAIL();
		}

		// Confirm correct default time
		if (sample.hour() != NULL) {
			failOut("Invalid epoch time provided by sample");
			fpOut("Time expected", "00:00:00:000");
			fpOut("Time given", sample.time());
			std::cout << "\n\t\t-> Invalid hour" << std::endl;
			FAIL();
		}

		if (sample.minute() != NULL) {
			failOut("Invalid epoch time provided by sample");
			fpOut("Time expected", "00:00:00:000");
			fpOut("Time given", sample.time());
			std::cout << "\n\t\t-> Invalid minute" << std::endl;
			FAIL();
		}

		if (sample.second() != NULL) {
			failOut("Invalid epoch time provided by sample");
			fpOut("Time expected", "00:00:00:000");
			fpOut("Time given", sample.time());
			std::cout << "\n\t\t-> Invalid second" << std::endl;
			FAIL();
		}

		if (sample.millisecond() != NULL) {
			failOut("Invalid epoch time provided by sample");
			fpOut("Time expected", "00:00:00:000");
			fpOut("Time given", sample.time());
			std::cout << "\n\t\t-> Invalid millisecond" << std::endl;
			FAIL();
		}

		// Confirm correct epoch JDN calculation
		if (sample.toJulianDayNumber() != MIN_JDN) {
			failOut("Invalid epoch JDN provided by sample");
			fpOut("JDN expected", MIN_JDN);
			fpOut("JDN given", sample.toJulianDayNumber());
			std::cout << std::endl;
			FAIL();
		}

		// Confirm datetimes aknowledgement of epoch
		if (!sample.isEpoch()) {
			failOut("Invalid epoch evaluation provided by sample");
			fpOut("Datetime", sample);
			fpOut("VDatetimeEx::isEpoch() eval", sample.isEpoch());
			std::cout << std::endl;
			FAIL();
		}

		// Objective Truths At This Point:
		// -> Sample Datetime is January 1, 1970, midnight
		// -> The minimum JDN has been calculated correctly
		// -> Every date JDN thereafter should be the last plus 1

		msgOut("Testing all possible dates: ('");
		std::cout
			<< VDate{ MIN_JDN }.dateStr(VDate::Format::STANDARD)
			<< "' through '"
			<< VDate{ MAX_JDN }.dateStr(VDate::Format::STANDARD)
			<< "')...\n";

		VDatetimeEx::JDN lastJDN{ sample.toJulianDayNumber() };
		VDatetimeEx::JDN expectedJDN{ (lastJDN + (double)1.) };
		uint32_t datesVerified{ 0 };

		// Confirm all possible dates yeild accurate JDN calculation
		while (expectedJDN <= MAX_JDN) {

			// Increase date without use of internal JDN system
			sample.getDate()->getDay()->increase(1);

			// Confirm sample JDN is just one after the last
			if (sample.toJulianDayNumber() != expectedJDN) {
				failOut("JDN divergence located at '");
				std::cout
					<< sample.datetimeStr(VDate::Format::STANDARD)
					<< "' date:";
				fpOut("JDN expected", expectedJDN);
				fpOut("JDN recieved", sample.toJulianDayNumber());
				fpOut("JDN divergence", expectedJDN);
				std::cout << " days\n\t\t"
					<< " -> Failed after testing "
					<< datesVerified << " dates"
					<< std::endl;
				FAIL();
			}

			// Adjust loop control variables
			lastJDN = sample.toJulianDayNumber();
			++datesVerified;
			++expectedJDN;

		}

		msgOut("Confirmed ");
		std::cout
			<< datesVerified
			<< " JDN calculations"
			<< std::endl;

		// Confirm all possible dates were tested
		if (datesVerified != REPR_COUNT) {
			failOut("Failed to test all possible dates");
			failOut("Results inconclusive");
			FAIL();
		}
	}


	// Tests if VDatetimeEx class produces accurate dates from JDN values
	TEST(VDtExJDNIntegrityTests, DateJDNInterpretationTest)
	{
		// This test relies on JDN calculation integrity!

		VDatetimeEx variableDt{};// January 1, 1970 00:00:00:000

		msgOut("This test relies on JDN calculation integrity!\n");
		msgOut("Testing all possible dates: ('");
		std::cout
			<< VDate{ MIN_JDN }.dateStr(VDate::Format::STANDARD)
			<< "' through '"
			<< VDate{ MAX_JDN }.dateStr(VDate::Format::STANDARD)
			<< "')...\n";

		uint32_t datesVerified{ 0 };

		while (datesVerified != REPR_COUNT) {

			// Designated test sample
			VDatetimeEx sample{ variableDt.toJulianDayNumber() };

			// Confirm lossless Julian Day Number interpretation
			if (sample.toJulianDayNumber() != variableDt.toJulianDayNumber()) {
				failOut("JDN information loss detected at '");
				std::cout
					<< variableDt.datetimeStr(VDate::Format::STANDARD)
					<< "' date:";
				fpOut("Datetime expected", variableDt);
				fpOut("Datetime recieved", sample);
				fpOut("JDN expected", variableDt.toJulianDayNumber());
				fpOut("JDN recieved", sample.toJulianDayNumber());
				fpOut(
					"JDN divergence",
					(sample.toJulianDayNumber() - variableDt.toJulianDayNumber())
				);
				std::cout
					<< " days\n\t\t"
					<< " -> Failed after testing "
					<< datesVerified << " dates"
					<< std::endl;
				FAIL();
			}

			// Confirm operator yeilds equality
			if (sample != variableDt) {
				failOut("Inequality detected by class operator with '");
				std::cout
					<< variableDt.datetimeStr(VDate::Format::STANDARD)
					<< "' date:";
				fpOut("Datetime given", sample);
				fpOut("JDN expected", variableDt.toJulianDayNumber());
				fpOut("JDN recieved", sample.toJulianDayNumber());
				std::cout << std::endl;
				FAIL();
			}

			// Adjust loop control variables
			++datesVerified;
			variableDt.getDate()->getDay()->increase(1);

		}

		msgOut("Confirmed ");
		std::cout
			<< datesVerified
			<< " JDN interpretations"
			<< std::endl;
	}

}
