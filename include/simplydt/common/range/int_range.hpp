
#ifndef SIMPLYDTLIB_L_INTEGER_RANGE_H_
#define SIMPLYDTLIB_L_INTEGER_RANGE_H_



#include<utility>
#include<limits>
#include<ostream>



/* /// \\\ /// \\\ /// \\\ /// | DEV NOTES | \\\ /// \\\ /// \\\ /// \\\ *\
* 
* > RULES GOVERNED IN THIS CLASS:
*	-> A range consist of a starting, ending, and position
*	   integer.
*	-> A range may only consist of positive integers.
*	-> All member methods assume attributes to be valid.
*	-> A ranges starting integer can never be greater than
*	   its ending integer.
*	-> A ranges ending integer can never be less than
*	   its starting integer.
*	-> A range is inclusive of its edges.
*	-> A ranges position can never be outside the bounds
*	   of the ranges starting and ending integers.
*		> (Except in case of boundless ranges)
*		> (If a non-boundless range position seeks to exceed
*		  its ending integer, it will wrap back around to the
*		  starting integer, the same vice versa)
*	-> In the absence of a range constructor parameter, its
*	   value will be defaulted to 0.
*	-> An incorrectly constructed range will result in
*	   normalization.
*	-> A range with an equal starting and ending integer
*	   constitutes a boundless range starting from the
*	   given equal value.
*	-> A boundless range can only account for integers that
*	   can be represented with the amount of bytes available
*	   to a given integer type.
*		> (If a boundless range seeks to exceed an integer
*		  types maximum, it will overflow!)
* 
\* /// \\\ /// \\\ /// \\\ ///    | END |    \\\ /// \\\ /// \\\ /// \\\ */



/* Range of positive integers */
template <typename UInt_T>
class Range {

public:
	/* Integer range from start to stop, starting at position */
	Range(UInt_T start, UInt_T stop, UInt_T position) noexcept
		: m_rangeStart{ start },
		m_rangeEnd{ stop },
		m_position{ position }
	{
		this->normalizeAttributes();
	}

	/* Integer range from start to stop, starting at 0 */
	Range(UInt_T start, UInt_T stop) noexcept
		: m_rangeStart{ start },
		m_rangeEnd{ stop },
		m_position{ start }
	{
		this->normalizeAttributes();
	}

	/* Integer range from 0 to stop, starting at 0 */
	Range(UInt_T stop) noexcept
		: m_rangeStart{ (UInt_T)0 },
		m_rangeEnd{ stop },
		m_position{ (UInt_T)0 }
	{
		this->normalizeAttributes();
	}

	/* Copy constructor */
	Range(const Range<UInt_T>& range) noexcept
		: m_rangeStart{ range.m_rangeStart },
		m_rangeEnd{ range.m_rangeEnd },
		m_position{ range.m_position }
	{
		this->normalizeAttributes();
	}

	/* Move constructor */
	Range(Range<UInt_T>&& range) noexcept
		: m_rangeStart{ static_cast<UInt_T&&>(range.m_rangeStart) },
		m_rangeEnd{ static_cast<UInt_T&&>(range.m_rangeEnd) },
		m_position{ static_cast<UInt_T&&>(range.m_position) }
	{
		this->normalizeAttributes();
	}

	virtual ~Range() = default;

	/* Range position translation result (laps, position) */
	using TranslateResult = std::pair<UInt_T, UInt_T>;

	/* Range translation modes */
	enum Translate {
		NEUTRAL,// No translation
		POSITIVE,// Positive translation
		NEGATIVE,// Negative translation
	};

	friend std::ostream& operator<<(std::ostream& os, const Range& range) noexcept
	{
		os << '[' << range.m_rangeStart << " - " << range.rangeEnd() << ']';

		return os;
	}

	/* Returns adopted integer type maximum representable value */
	static size_t integerTypeMax() noexcept
	{
		return (size_t)std::numeric_limits<UInt_T>::max();
	}

	Range& operator=(const Range<UInt_T>& range) noexcept
	{
		if (this == &range)
			return *this;
		
		this->m_rangeStart = range.m_rangeStart;
		this->m_rangeEnd = range.m_rangeEnd;
		this->m_position = range.m_position;

		return *this;
	}

	Range& operator=(Range<UInt_T>&& r_range) noexcept
	{
		if (this == &r_range)
			return *this;
		
		this->m_rangeStart = std::move(r_range.m_rangeStart);
		this->m_rangeEnd = std::move(r_range.m_rangeEnd);
		this->m_position = std::move(r_range.m_position);

		return *this;
	}

	/* Returns true if both ranges have same start, end, and position attributes */
	bool operator==(const Range<UInt_T>& range) const noexcept
	{
		bool matchingStart{ (this->m_rangeStart == range.m_rangeStart) };
		bool matchingEnd{ (this->m_rangeEnd == range.m_rangeEnd) };
		bool matchingPos{ (this->m_position == range.m_position) };

		return (matchingStart && matchingEnd && matchingPos);
	}

	/* Returns true if provided integer is within range bounds */
	bool operator[](UInt_T integer) const noexcept
	{
		return this->isWithinRange(integer);
	}

	/* Returns range starting integer */
	const UInt_T& rangeStart() const noexcept
	{
		return this->m_rangeStart;
	}

	/* Returns range ending integer */
	const UInt_T rangeEnd() const noexcept
	{
		if (this->m_rangeStart == this->m_rangeEnd)
			return this->integerTypeMax();

		return this->m_rangeEnd;
	}

	/* Returns total number of integers within range limitation */
	UInt_T rangeSize() const noexcept
	{
		return (UInt_T)(this->rangeEnd() - this->m_rangeStart + 1);// +1 to convert 0-index
	}

	/* Returns range position */
	const UInt_T& position() const noexcept
	{
		return this->m_position;
	}

	/* Returns true if range is all positive integers within limitation */
	bool isBoundless() const noexcept
	{
		return (this->m_rangeStart == this->m_rangeEnd);
	}

	/* Returns true if provided integer is within range bounds */
	bool isWithinRange(UInt_T integer) const noexcept
	{
		if (this->isBoundless() && integer >= this->m_rangeStart)
			return true;
		
		if (integer < this->m_rangeStart)
			return false;
		
		if (integer > this->rangeEnd())
			return false;
		
		return true;
	}

	/* Returns total number of units position is from range start */
	UInt_T displacement() const noexcept
	{
		if (this->isBoundless())
			return (UInt_T)(this->m_position - this->m_rangeStart);

		return (UInt_T)(this->m_position - this->m_rangeStart);
	}

	/* Returns total number of units until range position is at provided position */
	UInt_T untilPosition(UInt_T pos) const noexcept
	{
		if (!this->isWithinRange(pos))
			return (UInt_T)0;

		if (pos == this->m_position)
			return (UInt_T)0;
		
		if (pos < this->m_position) {
			UInt_T remain{ (UInt_T)((this->rangeEnd() - this->m_position) + 1) };// +1 for wrap around
			UInt_T gap{ (UInt_T)(pos - this->m_rangeStart) };

			return (UInt_T)(remain + gap);
		}
		else
			return (UInt_T)(pos - this->m_position);
	}

	/* Returns total number of units until position is at range start */
	UInt_T untilStart() const noexcept
	{
		return this->untilPosition(this->m_rangeStart);
	}

	/* Returns total number of units until position is at range end */
	UInt_T untilEnd() const noexcept
	{
		return this->untilPosition(this->rangeEnd());
	}
	
	/* Returns true if range position is at range start */
	bool isAtStart() const noexcept
	{
		return (this->m_position == this->m_rangeStart);
	}

	/* Returns true if range position is at range end */
	bool isAtEnd() const noexcept
	{
		return (this->m_position == this->rangeEnd());
	}

	/* Returns true if provided units overflow range position in positive direction */
	bool causesOverflow(UInt_T add_units) const noexcept
	{
		if (add_units == (UInt_T)0)
			return false;

		if (this->isAtEnd())
			return true;
		
		if (this->untilEnd() < add_units)
			return true;

		return false;
	}

	/* Returns true if provided units overflow range position in negative direction */
	bool causesUnderflow(UInt_T add_units) const noexcept
	{
		if (add_units == (UInt_T)0)
			return false;

		if (this->isAtStart())
			return true;
		
		if (this->displacement() < add_units)
			return true;

		return false;
	}

	/* Returns true if provided units overflow range position in either direction */
	bool causesRangeOverflow(UInt_T add_units) const noexcept
	{
		return (this->causesOverflow(add_units) || this->causesUnderflow(add_units));
	}

	/* Returns calculated range position translation */
	TranslateResult calculateTranslation(Translate direction, UInt_T add_units) const noexcept
	{
		UInt_T laps{ 0 };
		UInt_T position{ this->m_position };

		if (add_units == (UInt_T)0 || direction == NEUTRAL)
			return TranslateResult{ laps, position };

		if (this->isBoundless()) {
			// Not calculating laps here because this is boundless
			// Boundless range overflows occur here
			position += add_units;

			return TranslateResult{ laps, position };
		}


		switch (direction) {
		// Positive translation
		case POSITIVE:
			position += add_units;

			laps = (UInt_T)(
				(position - this->m_rangeStart) / this->rangeSize()
			);

			/***************************************************************************\
			*            vvv           AI GENERATED CODE BELOW           vvv            *
			\***************************************************************************/

			position = (
				this->m_rangeStart + (position - this->m_rangeStart) % this->rangeSize()
			);

			/***************************************************************************\
			*            ^^^           AI GENERATED CODE ABOVE           ^^^            *
			\***************************************************************************/

			return TranslateResult{ laps, position };


		// Negative translation
		case NEGATIVE:
			/***************************************************************************\
			*            vvv           AI GENERATED CODE BELOW           vvv            *
			\***************************************************************************/

			if (position < this->m_rangeStart + add_units) {
				laps = (
					1 + (this->m_rangeStart - position + add_units - 1)
					/ this->rangeSize()
				);

				position = (
					this->rangeEnd() - (this->m_rangeStart - position + add_units - 1)
					% this->rangeSize()
				);
			}
			else
				position -= add_units;

			/***************************************************************************\
			*            ^^^           AI GENERATED CODE ABOVE           ^^^            *
			\***************************************************************************/

			return TranslateResult{ laps, position };
		}
		
		return TranslateResult{ laps, position };
	}

	/* Returns calculated positive range position translation */
	TranslateResult calculatePositiveTrans(UInt_T add_units) const noexcept
	{
		return this->calculateTranslation(Translate::POSITIVE, add_units);
	}

	/* Returns calculated negative range position translation */
	TranslateResult calculateNegativeTrans(UInt_T add_units) const noexcept
	{
		return this->calculateTranslation(Translate::NEGATIVE, add_units);
	}

	/* Set range position */
	bool setPosition(UInt_T pos) noexcept
	{
		if (!this->isWithinRange(pos))
			return false;

		this->m_position = pos;

		return true;
	}

	/* Translate range position in provided direction with provided units and return laps */
	UInt_T translate(Translate direction, UInt_T add_units) noexcept
	{
		TranslateResult destination{
			this->calculateTranslation(direction, add_units)
		};

		this->setPosition(destination.second);

		return destination.first;
	}

	/* Set range starting integer */
	bool setRangeStart(UInt_T start) noexcept
	{
		if (!this->isValidStartingInteger(start))
			return false;
		
		this->m_rangeStart = start;
		
		return true;
	}

	/* Set range ending integer */
	bool setRangeEnd(UInt_T stop) noexcept
	{
		if (!this->isValidEndingInteger(stop))
			return false;
		
		this->m_rangeEnd = stop;
		
		return true;
	}

	/* Increase range position provided number of units */
	void increment(UInt_T add_units = (UInt_T)1) noexcept
	{
		this->translate(Translate::POSITIVE, add_units);
	}

	/* Decrease range position provided number of units */
	void decrement(UInt_T add_units = (UInt_T)1) noexcept
	{
		this->translate(Translate::NEGATIVE, add_units);
	}

	/* Reset range position to starting integer */
	void reset() noexcept
	{
		this->setPosition(this->m_rangeStart);
	}


private:
	UInt_T m_rangeStart;
	UInt_T m_rangeEnd;
	UInt_T m_position;

	bool isValidStartingInteger(UInt_T integer) const noexcept
	{
		if (integer == (UInt_T)0)
			return true;

		if (integer > this->m_rangeEnd)
			return false;

		if (integer > this->m_position)
			return false;

		return true;
	}

	bool isValidEndingInteger(UInt_T integer) const noexcept
	{
		if (integer == (UInt_T)0)
			return true;

		if (integer < this->m_rangeStart)
			return false;

		if (this->m_position > integer)
			return false;

		return true;
	}

	bool causesIntegerTypeOverflow(UInt_T add_units) const noexcept
	{
		if (!this->isBoundless())
			return false;

		UInt_T untilLimit{ (this->integerTypeMax() - this->position()) };

		return (untilLimit < add_units);
	}

	void normalizeAttributes() noexcept
	{
		if (this->m_rangeStart > this->m_rangeEnd)
			this->m_rangeStart = (UInt_T)0;
		
		// Start position is greater than end but range is NOT boundless
		if (this->m_position > this->m_rangeEnd && !this->isBoundless())
			this->reset();
		
		// Start position is less than start
		if (this->m_position < this->m_rangeStart)
			this->reset();
	}

};



#endif // SIMPLYDTLIB_L_INTEGER_RANGE_H_
