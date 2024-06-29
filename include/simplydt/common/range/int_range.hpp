
#ifndef SIMPLYDTLIB_L_INTEGER_RANGE_H_
#define SIMPLYDTLIB_L_INTEGER_RANGE_H_



#include<utility>


/* Range of positive integers */
template <typename UInt_T>
class Range {

public:
	/* Integer range from start to stop starting at position */
	Range(UInt_T start, UInt_T stop, UInt_T position) noexcept
		: m_rangeStart{ start },
		m_rangeEnd{ stop },
		m_position{ position }
	{
		//
	}

	/* Integer range from start to stop starting at 0 */
	Range(UInt_T start, UInt_T stop) noexcept
		: m_rangeStart{ start },
		m_rangeEnd{ stop },
		m_position{ start }
	{
		//
	}

	/* Integer range from 0 to stop starting at 0 */
	Range(UInt_T stop) noexcept
		: m_rangeStart{ (UInt_T)0 },
		m_rangeEnd{ stop },
		m_position{ (UInt_T)0 }
	{
		//
	}

	/* Copy constructor */
	Range(const Range<UInt_T>& range) noexcept
		: m_rangeStart{ range.m_rangeStart },
		m_rangeEnd{ range.m_rangeEnd },
		m_position{ range.m_position }
	{
		//
	}

	/* Move constructor */
	Range(Range<UInt_T>&& range) noexcept
		: m_rangeStart{ static_cast<UInt_T&&>(range.m_rangeStart) },
		m_rangeEnd{ static_cast<UInt_T&&>(range.m_rangeEnd) },
		m_position{ static_cast<UInt_T&&>(range.m_position) }
	{
		//
	}

	~Range() = default;

	/* Range position translation results */
	using TranslateResult = std::pair<UInt_T, UInt_T>;

	/* Range translation modes */
	enum Translate {
		NEUTRAL,// No translation
		POSITIVE,// Positive translation
		NEGATIVE,// Negative translation
	};

	Range& operator=(const Range<UInt_T>& range) noexcept;
	Range& operator=(Range<UInt_T>&& r_range) noexcept;
	/* Returns true if both ranges have same start, end, and position */
	bool operator==(const Range<UInt_T>& range) const noexcept;
	/* Returns true if provided integer is within range bounds */
	bool operator[](UInt_T integer) const noexcept;

	/* Returns range starting integer */
	const UInt_T& rangeStart() const noexcept;
	/* Returns range ending integer */
	const UInt_T& rangeEnd() const noexcept;
	/* Returns range position */
	const UInt_T& position() const noexcept;
	/* Returns true if range is all positive integers */
	bool isBoundless() const noexcept;
	/* Returns true if provided integer is within range bounds */
	bool isWithinRange(UInt_T integer) const noexcept;
	/* Returns total number of units position is from range start */
	UInt_T displacement() const noexcept;
	/* Returns total number of units until range position is at provided position */
	UInt_T untilPosition(UInt_T pos) const noexcept;
	/* Returns total number of units until position is at range end */
	UInt_T untilEnd() const noexcept;
	/* Returns true if range position is at range start */
	bool isAtStart() const noexcept;
	/* Returns true if range position is at range end */
	bool isAtEnd() const noexcept;
	/* Returns true if provided units overflow range position in positive direction */
	bool causesOverflow(UInt_T add_units) const noexcept;
	/* Returns true if provided units overflow range position in negative direction */
	bool causesUnderflow(UInt_T add_units) const noexcept;
	/* Returns true if provided units overflow range position in either direction */
	bool causesRangeOverflow(UInt_T add_units) const noexcept;
	/* Returns calculated range position translation */
	TranslateResult calculateTranslation(Translate direction, UInt_T add_units) const noexcept;
	/* Returns calculated positive range position translation */
	TranslateResult calculatePositiveTrans(UInt_T add_units) const noexcept;
	/* Returns calculated negative range position translation */
	TranslateResult calculateNegativeTrans(UInt_T add_units) const noexcept;
	/* Translate range position in provided direction with provided units and return laps */
	UInt_T translate(Translate direction, UInt_T add_units) noexcept;
	/* Set range starting integer */
	void setRangeStart(UInt_T start) noexcept;
	/* Set range ending integer */
	void setRangeEnd(UInt_T stop) noexcept;
	/* Increase range position provided number of units */
	void increment(UInt_T add_units = (UInt_T)1) noexcept;
	/* Decrease range position provided number of units */
	void decrement(UInt_T add_units = (UInt_T)1) noexcept;
	/* Reset range position to starting integer */
	void reset() noexcept;


private:
	UInt_T m_rangeStart;
	UInt_T m_rangeEnd;
	UInt_T m_position;

	bool isValidStartingInteger(UInt_T integer) const noexcept;
	bool isValidEndingInteger(UInt_T integer) const noexcept;
	bool causesIntegerTypeOverflow(UInt_T add_units) const noexcept;
	void normalizeAttributes() noexcept;

};



#endif // SIMPLYDTLIB_L_INTEGER_RANGE_H_
