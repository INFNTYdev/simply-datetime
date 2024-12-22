
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//    GREGORIAN CALENDAR UTILITY BENCHMARK TESTS    //
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//



#include<random>
#include<benchmark/benchmark.h>
#include"simplydt/gregorian_calendar/gregorian_util.hpp"


static void validateYear_bm(benchmark::State& state)
{
	const uint16_t testYear{ 2024 };

	for (auto _ : state) {

		benchmark::DoNotOptimize(
			SimplyDt::GregorianCalendar::Util::isValidYear(testYear)
		);

	}
}
