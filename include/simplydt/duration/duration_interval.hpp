
#ifndef SIMPLYDTLIB_L_DURATION_INTERVAL_H_
#define SIMPLYDTLIB_L_DURATION_INTERVAL_H_



#include"simplydt/common/interval/interval.hpp"


/* Datetime duration interval */
class DurationInterval : public Interval<uint16_t> {

public:
	DurationInterval(uint16_t cmax, uint16_t cstart, uint16_t pos) noexcept
		: Interval<uint16_t>{ cmax, cstart, pos }
	{
		//
	}

	DurationInterval(uint16_t cmax, uint16_t cstart) noexcept
		: Interval<uint16_t>{ cmax, cstart }
	{
		//
	}

	DurationInterval(const DurationInterval& dur_interval) noexcept
		: Interval<uint16_t>{ dur_interval }
	{
		//
	}

	DurationInterval(DurationInterval&& dur_interval) noexcept
		: Interval<uint16_t>{
			std::forward<DurationInterval>(dur_interval)
		}
	{
		//
	}

	virtual ~DurationInterval() noexcept = default;

	//DurationInterval& operator=(const DurationInterval& dur_interval) noexcept;// <--- No need for this at the moment

	//DurationInterval& operator=(DurationInterval&& dur_interval) noexcept;// <--- No need for this at the moment

	/* Returns duration interval value in double digit format */
	std::string toDoubleDigitStr() const noexcept
	{
		if (this->position() > (uint16_t)9U && this->position() <= (uint16_t)99U)
            return this->toStr();

        if (this->position() < (uint16_t)10U)
            return std::string{ ('0' + this->toStr()) };

        std::string posStr{ this->toStr() };

        return posStr.substr((posStr.size() - (size_t)2));
	}

};



#endif // SIMPLYDTLIB_L_DURATION_INTERVAL_H_
