
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
        this->constructNodeVector(std::forward<Interval_T&&>(intervals)...);
    }

    virtual ~LinkedSequence() noexcept = default;

    /* Returns total number of linked intervals in sequence */
    size_t linkSize() const noexcept
    {
        return this->m_intervals.size();
    }

    /* Returns linked interval at provided index if any */
    Interval<UInt_T>* getInterval(size_t index) noexcept
    {
        if (index >= this->linkSize())
            return nullptr;
        
        return this->m_intervals[index].get();
    }


private:
    std::vector<IntervalNode> m_intervals;

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

        bool linkSuccess{ false };

        // Link intervals
        for (size_t r{ (this->linkSize() - (size_t)1ULL) }; r > 0; --r) {

            size_t precedingIndex{ (r - (size_t)1ULL) };

            linkSuccess = this->m_intervals[r]->linkPrecedingInterval(
                *(this->m_intervals[precedingIndex])
            );

            // This shouldn't happen
            if (!linkSuccess)
                break;

        }
    }

};



#endif // SIMPLYDTLIB_L_INTERVAL_SEQUENCE_LINK_H_
