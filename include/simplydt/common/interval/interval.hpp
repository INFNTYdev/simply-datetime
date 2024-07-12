
#ifndef SIMPLYDTLIB_L_INTERVAL_H_
#define SIMPLYDTLIB_L_INTERVAL_H_



#include<string>

#include"simplydt/common/range/int_range.hpp"


/* Linkable counting interval */
template <typename UInt_T>
class Interval {

public:
	/* Interval position translation result */
	using TransResult = Range<UInt_T>::TranslateResult;
	/* Large interval position translation result */
	using LargeTransResult = Range<UInt_T>::LargeTranslateResult;
	/* Interval translation modes */
	using Trans = Range<UInt_T>::Translate;

	Interval(UInt_T cmax, UInt_T cstart, UInt_T pos) noexcept
		: m_range{ cstart, cmax, pos },
		m_preceding_ptr{ nullptr },
		m_subsequent_ptr{ nullptr }
	{
		//
	}

	Interval(UInt_T cmax, UInt_T cstart) noexcept
		: m_range{ cstart, cmax },
		m_preceding_ptr{ nullptr },
		m_subsequent_ptr{ nullptr }
	{
		//
	}

	Interval(UInt_T cmax) noexcept
		: m_range{ cmax },
		m_preceding_ptr{ nullptr },
		m_subsequent_ptr{ nullptr }
	{
		//
	}

	Interval(const Interval<UInt_T>& interval) noexcept
		: m_range{ interval.m_range },
		m_preceding_ptr{ nullptr },
		m_subsequent_ptr{ nullptr }
	{
		//
	}

	Interval(Interval<UInt_T>&& r_interval) noexcept
		: m_range{ std::move(r_interval.m_range) },
		m_preceding_ptr{ std::move(r_interval.m_preceding_ptr) },
		m_subsequent_ptr{ std::move(r_interval.m_subsequent_ptr) }
	{
		//
	}

	virtual ~Interval() = default;

	friend std::ostream& operator<<(std::ostream& os, const Interval<UInt_T>& interval) noexcept
	{
		os << interval.toStr();

		return os;
	}

	Interval& operator=(const Interval<UInt_T>& interval) noexcept
	{
		if (this == &interval)
			return *this;
		
		this->m_range = interval.m_range;
		this->m_preceding_ptr = nullptr;
		this->m_subsequent_ptr = nullptr;

		return *this;
	}

	Interval& operator=(Interval<UInt_T>&& r_interval) noexcept
	{
		if (this == &r_interval)
			return *this;
		
		this->m_range = std::move(r_interval.m_range);
		this->m_preceding_ptr = nullptr;
		this->m_subsequent_ptr = nullptr;

		return *this;
	}
	
	/* Returns true if both intervals have same start, end, and position attributes */
	template <typename Other_UInt_T>
	bool operator==(const Interval<Other_UInt_T>& interval) const noexcept
	{
		if (!this->isSameRange(interval))
			return false;
		
		if (this->m_range.position() != interval.m_range.position())
			return false;
		
		return true;
	}

	/* Returns interval starting position */
	const UInt_T& startPosition() const noexcept
	{
		return this->m_range.rangeStart();
	}

	/* Returns interval ending position */
	UInt_T threshold() const noexcept
	{
		return this->m_range.rangeEnd();
	}

	/* Returns interval position */
	const UInt_T& position() const noexcept
	{
		return this->m_range.position();
	}

	/* Returns total number of integers within interval limitations */
	UInt_T size() const noexcept
	{
		return this->m_range.rangeSize();
	}

	/* Returns true if interval counts all positive integers within limitation */
	bool isBoundless() const noexcept
	{
		return this->m_range.isBoundless();
	}

	/* Returns true if interval is linked with a leading interval */
	bool hasPrecedingInterval() const noexcept
	{
		return (this->m_preceding_ptr != nullptr);
	}

	/* Returns true if interval is linked with a trailing interval */
	bool hasSubsequentInterval() const noexcept
	{
		return (this->m_subsequent_ptr != nullptr);
	}

	/* Returns total number of units position is from starting position */
	UInt_T displacement() const noexcept
	{
		return this->m_range.displacement();
	}

	/* Returns total number of units until position is at provided position */
	UInt_T untilPosition(UInt_T pos) const noexcept
	{
		return this->m_range.untilPosition(pos);
	}

	/* Returns total number of units until position is at provided intervals position */
	UInt_T untilPosition(const Interval<UInt_T>& interval) const noexcept
	{
		return this->m_range.untilPosition(interval.position());
	}

	/* Returns total number of units until position is at starting position */
	UInt_T untilStart() const noexcept
	{
		return this->m_range.untilStart();
	}

	/* Returns total number of units until position is at ending position */
	UInt_T untilThreshold() const noexcept
	{
		return this->m_range.untilEnd();
	}

	/* Returns true if position is at start */
	bool isAtStart() const noexcept
	{
		return this->m_range.isAtStart();
	}

	/* Returns true if position is at ending position */
	bool isAtThreshold() const noexcept
	{
		return this->m_range.isAtEnd();
	}

	/* Returns string representation of interval position */
	std::string toStr() const noexcept
	{
		return std::to_string(this->m_range.position());
	}

	/* Returns true if both intervals have same starting and stoping positions */
	template <typename Other_UInt_T>
	bool isSameRange(const Interval<Other_UInt_T>& interval) const noexcept
	{
		if ((size_t)this->startPosition() != (size_t)interval.startPosition())
			return false;
		
		if ((size_t)this->threshold() != (size_t)interval.threshold())
			return false;
		
		return true;
	}

	/* Returns true if provided intervals position is greater than this position */
	template <typename Other_UInt_T>
	bool isBefore(const Interval<Other_UInt_T>& interval) const noexcept
	{
		return ((size_t)this->m_range.position() < (size_t)interval.m_range.position());
	}

	/* Returns true if provided intervals position is less than this position */
	template <typename Other_UInt_T>
	bool isAfter(const Interval<Other_UInt_T>& interval) const noexcept
	{
		return ((size_t)this->m_range.position() > (size_t)interval.m_range.position());
	}

	/* Link this interval with provided leading interval */
	bool linkPrecedingInterval(Interval<UInt_T>& interval) noexcept
	{
		if (this->hasPrecedingInterval() || interval.hasSubsequentInterval())
			return false;
		
		this->m_preceding_ptr = &interval;
		interval.m_subsequent_ptr = this;

		return true;
	}

	/* Set interval position */
	virtual bool setPosition(UInt_T pos) noexcept
	{
		return this->m_range.setPosition(pos);
	}

	/* Set interval ending position */
	bool setThreshold(UInt_T cmax) noexcept
	{
		return this->m_range.setRangeEnd(cmax);
	}

	/* Returns calculated interval position translation */
	virtual TransResult calculateTranslation(Trans trans, UInt_T units) const noexcept
	{
		return this->m_range.calculateTranslation(trans, units);
	}

	/* Returns calculated interval position translation */
	virtual LargeTransResult calculateLargeTranslation(Trans trans, size_t units) const noexcept
	{
		return this->m_range.calculateLargeTranslation(trans, units);
	}

	/* Translate position in provided direction with provided units */
	virtual void displace(Trans trans, UInt_T units) noexcept
	{
		TransResult destination{ this->m_range.calculateTranslation(trans, units) };

		this->m_range.setPosition(destination.second);

		if (this->hasPrecedingInterval() && destination.first)
			this->lap(trans, destination.first);
	}

	/* Translate position in provided direction with provided units */
	virtual void largeDisplace(Trans trans, size_t units) noexcept
	{
		LargeTransResult destination{
			this->m_range.calculateLargeTranslation(trans, units)
		};

		this->m_range.setPosition(destination.second);

		if (this->hasPrecedingInterval() && destination.first)
			this->largeLap(trans, destination.first);
	}

	/* Increase position provided number of units */
	virtual void increment(UInt_T units = (UInt_T)1) noexcept
	{
		this->displace(Trans::POSITIVE, units);
	}

	/* Increase position provided number of units */
	void largeIncrement(size_t units) noexcept
	{
		this->largeDisplace(Trans::POSITIVE, units);
	}

	/* Decrease position provided number of units */
	virtual void decrement(UInt_T units = (UInt_T)1) noexcept
	{
		this->displace(Trans::NEGATIVE, units);
	}

	/* Decrease position provided number of units */
	void largeDecrement(size_t units) noexcept
	{
		this->largeDisplace(Trans::NEGATIVE, units);
	}

	/* Reset interval position to starting position */
	virtual void reset() noexcept
	{
		this->m_range.reset();
	}


protected:
	/* Linked interval pointer */
	using LinkedInterval = Interval<UInt_T>*;

	/* Invoke displacement on preceding interval */
	virtual void lap(Trans trans, UInt_T lap_units) noexcept
	{
		if (!this->hasPrecedingInterval())
			return;
		
		this->m_preceding_ptr->displace(trans, lap_units);
	}

	/* Invoke displacement on preceding interval */
	virtual void largeLap(Trans trans, size_t lap_units) noexcept
	{
		if (!this->hasPrecedingInterval())
			return;

		this->m_preceding_ptr->largeDisplace(trans, lap_units);
	}

	/* Returns linked preceding interval */
	LinkedInterval getPreceding() const noexcept
	{
		return this->m_preceding_ptr;
	}

	/* Returns linked subsequent interval */
	LinkedInterval getSubsequent() const noexcept
	{
		return this->m_subsequent_ptr;
	}


private:
	Range<UInt_T> m_range;
	LinkedInterval m_preceding_ptr;
	LinkedInterval m_subsequent_ptr;

};



#endif // SIMPLYDTLIB_L_INTERVAL_H_
