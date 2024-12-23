
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//    DATETIME STRING UTILITY TESTS     //
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//



#include<gtest/gtest.h>
#include<cstdint>
#include<vector>
#include"simplydt/common/string/string_util.hpp"


namespace DTStringUtilityTests {

	TEST(StringUtilityTestSuite, IntegerToDoubleDigitString)
	{
		std::vector<std::pair<uint16_t, std::string>> testSet{
			{ 2024, "24" },
			{ 2000, "00" },
			{ 1970, "70" },
			{ 4444, "44" },
			{ 7777, "77" },
		};

		for (std::pair<uint16_t, std::string>& set : testSet) {

			const uint16_t* sample = &set.first;
			const char* expect = set.second.data();

			ASSERT_EQ(SimplyDt::String::toDoubleDigitStr(*sample), expect);

		}
	}

}
