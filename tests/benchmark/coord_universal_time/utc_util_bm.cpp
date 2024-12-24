
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//    COORDINATED UNIVERSAL TIME UTILITY BENCHMARKS     //
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//



#include<benchmark/benchmark.h>
#include"simplydt/coord_universal_time/utc_util.hpp"


namespace CoordinatedUniversalTimeBenchmark {

	static void BM_validateHour(benchmark::State& state)
    {
        const uint8_t testHour{ 15 };

        for (auto _ : state) {

            benchmark::DoNotOptimize(
                SimplyDt::CoordUniversalTime::Util::isValidHour(static_cast<const uint8_t&>(testHour))
            );

        }
    }
    BENCHMARK(BM_validateHour);

}
