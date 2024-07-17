
#ifndef SIMPLYDTLIB_L_INTERVAL_SEQUENCE_LINK_H_
#define SIMPLYDTLIB_L_INTERVAL_SEQUENCE_LINK_H_



#include<memory>
#include<vector>

#include"simplydt/common/interval/interval.hpp"


/* Sequence of linked intervals */
template <typename UInt_T, typename... Interval_T>
class LinkedSequence {

public:
    /* Sequence node */
    using IntervalNode = std::unique_ptr<Interval<UInt_T>>;

    LinkedSequence(Interval_T&&... intervals)
        : m_intervals{}
    {
        this->constructNodeVector(std::forward<Interval_T>(intervals)...);
    }

    LinkedSequence(const LinkedSequence<UInt_T, Interval_T...>& sequence) noexcept
        : m_intervals{}
    {
        for (const auto& interval : sequence.m_intervals)
            m_intervals.emplace_back(new Interval<UInt_T>(*interval));

        this->linkNodes();
    }

    LinkedSequence(LinkedSequence<UInt_T, Interval_T...>&& sequence) noexcept
        : m_intervals{ std::move(sequence.m_intervals) }
    {
        //
    }

    virtual ~LinkedSequence() noexcept = default;

    LinkedSequence<UInt_T, Interval_T...>& operator=(LinkedSequence<UInt_T, Interval_T...>&& sequence) noexcept
    {
        if (this == &sequence)
            return *this;

        this->m_intervals = std::move(sequence.m_intervals);

        return *this;
    }

    /* Returns total number of linked intervals in sequence */
    size_t linkSize() const noexcept
    {
        return this->m_intervals.size();
    }

    /* Returns linked interval at provided index if any */
    Interval<UInt_T>* getInterval(size_t index) const noexcept
    {
        if (index >= this->linkSize())
            return nullptr;
        
        return this->m_intervals[index].get();
    }

    /* Returns vector of pointer to linked intervals */
    std::vector<Interval<UInt_T>*> getIntervals() const noexcept
    {
        std::vector<Interval<UInt_T>*> intervals{};

        for (size_t index{ 0 }; index < this->linkSize(); ++index) {
            
            intervals.emplace_back(this->getInterval(index));

        }

        return intervals;
    }


private:
    std::vector<IntervalNode> m_intervals;

    bool linkNodes() noexcept
    {
        bool linkSuccess{ false };

        for (size_t r{ (this->linkSize() - (size_t)1ULL) }; r > 0; --r) {

            size_t precedingIndex{ (r - (size_t)1ULL) };

            linkSuccess = this->m_intervals[r]->linkPrecedingInterval(
                *(this->m_intervals[precedingIndex])
            );

            // This shouldn't happen
            if (!linkSuccess)
                return false;

        }

        return linkSuccess;
    }

    void constructNodeVector(Interval_T&&... nodes)
    {
        // Check vector contents first
        if (!this->m_intervals.empty())
            return;

        // Parenthesis to contain variadic denote
        (
            // Store r-value intervals
            m_intervals.emplace_back(
                std::make_unique<Interval_T>(std::move(nodes))
            ),
            ...
        );

        if (this->m_intervals.size() < 2)
            return;

        // Link intervals
        this->linkNodes();
    }

};



#endif // SIMPLYDTLIB_L_INTERVAL_SEQUENCE_LINK_H_
