
#ifndef SIMPLYDTLIB_L_INTERVAL_H_
#define SIMPLYDTLIB_L_INTERVAL_H_



#include<string>

#include"simplydt/common/range/int_range.hpp"


/* Linkable counting interval */
template <typename UInt_T>
class Interval {

	/* Interval position translation result */
	using TransResult = Range<UInt_T>::TranslateResult;
	/* Interval translation modes */
	using Trans = Range<UInt_T>::Translate;
	/* Linked interval pointer */
	using LinkedInterval = Interval<UInt_T>*;

public:
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
	bool setPosition(UInt_T pos) noexcept
	{
		return this->m_range.setPosition(pos);
	}

	/* Set linked preceding interval position */
	bool setPrecedingPosition(UInt_T pos) noexcept
	{
		if (!this->hasPrecedingInterval())
			return false;

		return this->m_preceding_ptr->setPosition(pos);
	}

	/* Set linked subsequent interval position */
	bool setSubsequentPosition(UInt_T pos) noexcept
	{
		if (!this->hasSubsequentInterval())
			return false;

		return this->m_subsequent_ptr->setPosition(pos);
	}

	/* Returns linked preceding interval position */
	size_t precedingPosition() const noexcept
	{
		if (!this->hasPrecedingInterval())
			return (size_t)0;

		return this->m_preceding_ptr->position();
	}

	/* Returns linked subsequent interval position */
	size_t subsequentPosition() const noexcept
	{
		if (!this->hasSubsequentInterval())
			return (size_t)0;

		return this->m_subsequent_ptr->position();
	}

	/* Returns calculated interval position translation */
	TransResult calculateTranslation(Trans trans, UInt_T units) const noexcept
	{
		return this->m_range.calculateTranslation(trans, units);
	}

	/* Returns calculated preceding interval position translation */
	TransResult calculatePrecedingTranslation(Trans trans, UInt_T units) const noexcept
	{
		if (!this->hasPrecedingInterval())
			return TransResult{ NULL, NULL };
		
		return this->m_preceding_ptr->calculateTranslation(trans, units);
	}

	/* Returns calculated subsequent interval position translation */
	TransResult calculateSubsequentTranslation(Trans trans, UInt_T units) const noexcept
	{
		if (!this->hasSubsequentInterval())
			return TransResult{ NULL, NULL };
		
		return this->m_subsequent_ptr->calculateTranslation(trans, units);
	}

	/* Translate position in provided direction with provided units */
	virtual void displace(Trans trans, UInt_T units) noexcept
	{
		TransResult destination{ this->m_range.calculateTranslation(trans, units) };

		this->m_range.setPosition(destination.second);

		if (this->hasPrecedingInterval() && destination.first)
			this->lap(trans, destination.first);
	}

	/* Translate linked preceding interval position in provided direction with provided units */
	void doPrecedingDisplace(Trans trans, UInt_T units) noexcept
	{
		if (!this->hasPrecedingInterval())
			return;
		
		this->m_preceding_ptr->displace(trans, units);
	}

	/* Translate linked subsequent interval position in provided direction with provided units */
	void doSubsequentDisplace(Trans trans, UInt_T units) noexcept
	{
		if (!this->hasSubsequentInterval())
			return;
		
		this->m_subsequent_ptr->displace(trans, units);
	}

	/* Increase position provided number of units */
	void increment(UInt_T units = (UInt_T)1) noexcept
	{
		this->displace(Trans::POSITIVE, units);
	}

	/* Increase linked preceding interval position provided number of units */
	void doPrecedingIncrement(UInt_T units = (UInt_T)1) noexcept
	{
		if (!this->hasPrecedingInterval())
			return;

		this->m_preceding_ptr->increment(units);
	}

	/* Increase linked subsequent interval position provided number of units */
	void doSubsequentIncrement(UInt_T units = (UInt_T)1) noexcept
	{
		if (!this->hasSubsequentInterval())
			return;

		this->m_subsequent_ptr->increment(units);
	}

	/* Decrease position provided number of units */
	void decrement(UInt_T units = (UInt_T)1) noexcept
	{
		this->displace(Trans::NEGATIVE, units);
	}

	/* Decrease linked preceding interval position provided number of units */
	void doPrecedingDecrement(UInt_T units = (UInt_T)1) noexcept
	{
		if (!this->hasPrecedingInterval())
			return;

		this->m_preceding_ptr->decrement(units);
	}

	/* Decrease linked subsequent interval position provided number of units */
	void doSubsequentDecrement(UInt_T units = (UInt_T)1) noexcept
	{
		if (!this->hasSubsequentInterval())
			return;

		this->m_subsequent_ptr->decrement(units);
	}

	/* Reset interval position to starting position */
	void reset() noexcept
	{
		this->m_range.reset();
	}


private:
	Range<UInt_T> m_range;
	LinkedInterval m_preceding_ptr;
	LinkedInterval m_subsequent_ptr;

	void lap(Trans trans, UInt_T lap_units) noexcept
	{
		if (!this->hasPrecedingInterval())
			return;
		
		this->m_preceding_ptr->displace(trans, lap_units);
	}

};



#endif // SIMPLYDTLIB_L_INTERVAL_H_
