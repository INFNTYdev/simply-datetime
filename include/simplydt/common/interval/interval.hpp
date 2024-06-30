
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
	using LinkedInterval = Interval<size_t>*;

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
		
		// INCOMPLETE!
		// What does it mean to set one interval equal to another existing?

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
	bool operator==(const Interval<UInt_T>& interval) const noexcept
	{
		if (!this->isSameRange(interval))
			return false;
		
		if (this->m_range.position() != interval.m_range.position())
			return false;
		
		return true;
	}

	/* Returns interval starting position */
	const UInt_T& startPosition() const noexcept;
	/* Returns interval ending position */
	UInt_T threshold() const noexcept;
	/* Returns interval position */
	const UInt_T& position() const noexcept;
	/* Returns total number of integers within interval limitations */
	UInt_T size() const noexcept;
	/* Returns true if interval counts all positive integers within limitation */
	bool isBoundless() const noexcept;
	/* Returns true if interval is linked with a leading interval */
	bool hasPrecedingInterval() const noexcept;
	/* Returns true if interval is linked with a trailing interval */
	bool hasSubsequentInterval() const noexcept;
	/* Returns total number of units position is from starting position */
	UInt_T displacement() const noexcept;
	/* Returns total number of units until position is at provided position */
	UInt_T untilPosition(UInt_T pos) const noexcept;
	/* Returns total number of units until position is at starting position */
	UInt_T untilStart() const noexcept;
	/* Returns total number of units until position is at ending position */
	UInt_T untilThreshold() const noexcept;
	/* Returns true if position is at start */
	bool isAtStart() const noexcept;
	/* Returns true if position is at ending position */
	bool isAtThreshold() const noexcept;

	/* Returns string representation of interval position */
	std::string toStr() const noexcept;
	/* Returns true if both intervals have same starting and stoping positions */
	template <typename Other_UInt_T>
	bool isSameRange(const Interval<Other_UInt_T>& interval) const noexcept;
	/* Link this interval with provided leading interval */
	template <typename Other_UInt_T>
	void linkPrecedingInterval(Interval<Other_UInt_T>& interval) noexcept;

	/* Set interval position */
	bool setPosition(UInt_T pos) noexcept;
	/* Set linked preceding interval position */
	bool setPrecedingPosition(UInt_T pos) noexcept;
	/* Set linked subsequent interval position */
	bool setSubsequentPosition(UInt_T pos) noexcept;
	/* Returns linked preceding interval position */
	const UInt_T& precedingPosition() const noexcept;
	/* Returns linked subsequent interval position */
	const UInt_T& subsequentPosition() const noexcept;
	/* Returns calculated interval position translation */
	TransResult calculateTranslation(Trans trans, UInt_T units) const noexcept;
	/* Returns calculated preceding interval position translation */
	TransResult calculatePrecedingTranslation(Trans trans, UInt_T units) const noexcept;
	/* Returns calculated subsequent interval position translation */
	TransResult calculateSubsequentTranslation(Trans trans, UInt_T units) const noexcept;
	/* Translate position in provided direction with provided units */
	virtual void displace(Trans trans, UInt_T units) noexcept;
	/* Translate linked preceding interval position in provided direction with provided units */
	void doPrecedingDisplace(Trans trans, UInt_T units) noexcept;
	/* Translate linked subsequent interval position in provided direction with provided units */
	void doSubsequentDisplace(Trans trans, UInt_T units) noexcept;
	/* Increase position provided number of units */
	void increment(UInt_T units = (UInt_T)1) noexcept;
	/* Increase linked preceding interval position provided number of units */
	void doPrecedingIncrement(UInt_T units = (UInt_T)1) noexcept;
	/* Increase linked subsequent interval position provided number of units */
	void doSubsequentIncrement(UInt_T units = (UInt_T)1) noexcept;
	/* Decrease position provided number of units */
	void decrement(UInt_T units = (UInt_T)1) noexcept;
	/* Decrease linked preceding interval position provided number of units */
	void doPrecedingDecrement(UInt_T units = (UInt_T)1) noexcept;
	/* Decrease linked subsequent interval position provided number of units */
	void doSubsequentDecrement(UInt_T units = (UInt_T)1) noexcept;
	/* Reset interval position to starting position */
	void reset() noexcept;


private:
	Range<UInt_T> m_range;
	LinkedInterval m_preceding_ptr;
	LinkedInterval m_subsequent_ptr;

	void lap(Trans trans, UInt_T lap_units) noexcept;

};



#endif // SIMPLYDTLIB_L_INTERVAL_H_
