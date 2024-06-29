
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

public:
	Interval(UInt_T cmax, UInt_T cstart, UInt_T pos) noexcept;
	Interval(UInt_T cmax, UInt_T cstart) noexcept;
	Interval(UInt_T cmax) noexcept;
	Interval(const Interval<UInt_T>& interval) noexcept;
	Interval(Interval<UInt_T>&& r_interval) noexcept;
	virtual ~Interval() = default;

	friend std::ostream& operator<<(std::ostream& os, const Interval<UInt_T>& interval) noexcept;

	Interval& operator=(const Interval<UInt_T>& interval) noexcept;
	Interval& operator=(Interval<UInt_T>&& r_interval) noexcept;
	
	/* Returns true if both intervals have same start, end, and position attributes */
	bool operator==(const Interval<UInt_T>& interval) noexcept;

	/* Returns interval starting position */
	const UInt_T& startPosition() const noexcept;
	/* Returns interval ending position */
	UInt_T threshold() const noexcept;
	/* Returns interval position */
	const UInt_T& position() const noexcept;
	/* Returns total number of integers within interval limitations */
	UInt_T size() const noexcept;
	/* Returns true if interval counts all positive integers */
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
	/* Link this interval with provided leading interval */
	void linkPrecedingInterval(Interval<UInt_T>& interval) noexcept;
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
	/* Decrease position provided number of units */
	void decrement(UInt_T units = (UInt_T)1) noexcept;
	/* Reset interval position to starting position */
	void reset() noexcept;


private:
	Range<UInt_T> m_range;
	Range<UInt_T>* m_preceding_ptr;
	Range<UInt_T>* m_subsequent_ptr;

	void lap(Trans trans, UInt_T lap_units) noexcept;

};



#endif // SIMPLYDTLIB_L_INTERVAL_H_
