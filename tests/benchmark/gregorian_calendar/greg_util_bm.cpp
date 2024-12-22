
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

    static void BM_validateLeapYear(benchmark::State& state)
    {
        const uint16_t testLeapYear{ 2024 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::isLeapYear(testLeapYear)
            );

        }
    }
    BENCHMARK(BM_validateLeapYear);

    static void BM_calculateMonthTotalDays(benchmark::State& state)
    {
        const uint16_t testYear{ 2020 };
        const uint8_t testMonth{ 6 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::getMonthTotalDays(
                    testYear,
                    testMonth
                )
            );

        }
    }
    BENCHMARK(BM_calculateMonthTotalDays);

    static void BM_validateDate(benchmark::State& state)
    {
        const uint16_t testYear{ 2001 };
        const uint8_t testMonth{ 2 };
        const uint8_t testDay{ 23 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::isValidDate(
                    testYear,
                    testMonth,
                    testDay
                )
            );

        }
    }
    BENCHMARK(BM_validateDate);

    static void BM_calculateYearTotalDays(benchmark::State& state)
    {
        const uint16_t testYear{ 2019 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::getYearTotalDays(testYear)
            );

        }
    }
    BENCHMARK(BM_calculateYearTotalDays);
    
}


BENCHMARK_MAIN();
