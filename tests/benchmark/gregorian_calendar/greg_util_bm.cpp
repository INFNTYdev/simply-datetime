
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

    static void BM_calculateMonthIndex(benchmark::State& state)
    {
        const uint8_t testMonth{ 5 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::getMonthIndex(testMonth)
            );

        }
    }
    BENCHMARK(BM_calculateMonthIndex);

    static void BM_getMonthName(benchmark::State& state)
    {
        const uint8_t testMonth{ 7 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::getMonth(testMonth)
            );

        }
    }
    BENCHMARK(BM_getMonthName);

    static void BM_getMonthAbbreviation(benchmark::State& state)
    {
        const uint8_t testMonth{ 1 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::getMonthAbbrev(testMonth)
            );

        }
    }
    BENCHMARK(BM_getMonthAbbreviation);

    static void BM_calculateDayOfWeekIndex(benchmark::State& state)
    {
        const uint16_t testYear{ 2016 };
        const uint8_t testMonth{ 6 };
        const uint8_t testDay{ 19 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::getDayOfWeekIndex(
                    testYear,
                    testMonth,
                    testDay
                )
            );

        }
    }
    BENCHMARK(BM_calculateDayOfWeekIndex);

    static void BM_getDayOfWeekName(benchmark::State& state)
    {
        const uint16_t testYear{ 2014 };
        const uint8_t testMonth{ 9 };
        const uint8_t testDay{ 21 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::getDayOfWeek(
                    testYear,
                    testMonth,
                    testDay
                )
            );

        }
    }
    BENCHMARK(BM_getDayOfWeekName);

    static void BM_getDayOfWeekAbbreviation(benchmark::State& state)
    {
        const uint16_t testYear{ 1972 };
        const uint8_t testMonth{ 12 };
        const uint8_t testDay{ 21 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::GregorianCalendar::Util::getDayOfWeekAbbrev(
                    testYear,
                    testMonth,
                    testDay
                )
            );

        }
    }
    BENCHMARK(BM_getDayOfWeekAbbreviation);

    static void BM_calculateDateFromJdn(benchmark::State& state)
    {
        const SimplyDt::JulianCalendar::JDN testJdn{ 2'440'587.5 };
        SimplyDt::GregorianCalendar::Date testDate{};

        for (auto _ : state) {

            SimplyDt::GregorianCalendar::Util::jdnToDate(testJdn, testDate);

        }
    }
    BENCHMARK(BM_calculateDateFromJdn);
    
}


BENCHMARK_MAIN();
