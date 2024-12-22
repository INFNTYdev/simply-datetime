
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

    static void BM_validateMonth(benchmark::State& state)
    {
        const uint8_t testMonth{ 3 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::isValidMonth(testMonth)
            );

        }
    }
    BENCHMARK(BM_validateMonth);

    static void BM_validateDay(benchmark::State& state)
    {
        const uint8_t testDay{ 30 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::isValidDay(testDay)
            );

        }
    }
    BENCHMARK(BM_validateDay);
    
}


BENCHMARK_MAIN();
