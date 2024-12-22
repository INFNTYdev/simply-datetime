
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//    GREGORIAN CALENDAR UTILITY BENCHMARKS     //
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//



#include<benchmark/benchmark.h>
#include"simplydt/gregorian_calendar/gregorian_util.hpp"


namespace GregorianCalendarBenchmark {

    static void BM_validateYear(benchmark::State& state)
    {
        const uint16_t testYear{ 2024 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::isValidYear(testYear)
            );

        }
    }
    BENCHMARK(BM_validateYear);
    
}


BENCHMARK_MAIN();
