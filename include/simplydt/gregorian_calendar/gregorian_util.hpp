
/*!
* @file gregorian_util.hpp
*
* @brief
* Gregorian calendar utilities document.
*
* @details
* Utilities for Gregorian calendar related functionality.
*/



#ifndef SIMPLYDT_L_SIMPLYDT_GREGORIAN_UTIL_H_
#define SIMPLYDT_L_SIMPLYDT_GREGORIAN_UTIL_H_



#include<cstdint>
#include<string_view>
#include"simplydt/gregorian_calendar/gregorian_defs.hpp"
#include"simplydt/julian_calendar/julian_defs.hpp"


namespace SimplyDt {

    namespace GregorianCalendar {

        /*!
        * @namespace SimplyDt::GregorianCalendar::Util
        *
        * @brief
        * Standard civil calendar utilities namespace.
        */
        namespace Util {

            /*!
            * @brief
            * Validate provided year.
            * 
            * @details
            * Evaluates if provided year is acceptable in
            * terms of the libraries capabilities.
            * 
            * @return
            * True if provided year is within acceptable
            * range
            */
            bool isValidYear(const uint16_t& year) noexcept;

            /*!
            * @brief
            * Validate provided month.
            * 
            * @return
            * True if provided month is within valid range
            */
            bool isValidMonth(const uint8_t& month) noexcept;

            /*!
            * @brief
            * Validate provided day.
            * 
            * @return
            * True if provided day is within valid range
            */
            bool isValidDay(const uint8_t& day) noexcept;

            /*!
            * @brief
            * Evaluate if provided year is a leap year.
            * 
            * @return
            * True if provided year is a leap year
            */
            bool isLeapYear(const uint16_t& year) noexcept;

            /*!
            * @brief
            * Determine total number of days in specified month.
            * 
            * @return
            * Total number of days in provided year-month
            * time frame.
            */
            uint8_t getMonthTotalDays(const uint16_t& year, const uint8_t& month) noexcept;

            /*!
            * @brief
            * Evaluate if provided date conforms to Gregorian
            * calendar rules.
            * 
            * @note
            * This evaluation also takes the libraries limitations
            * into account.
            * 
            * @return
            * True if provided date exist on Gregorian calendar
            */
            bool isValidDate(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept;// INCOMPLETE!

            /*!
            * @brief
            * Determine total number of days in specified year.
            * 
            * @return
            * Total number of days in provided year time frame.
            */
            uint16_t getYearTotalDays(const uint16_t& year) noexcept;

            /*!
            * @brief
            * Determine month index of specified month.
            * 
            * @return
            * Index of provided month
            */
            uint8_t getMonthIndex(const uint8_t& month) noexcept;

            /*!
            * @brief
            * Determine month name of specified month.
            * 
            * @return
            * Literal of provided month
            */
            const char* getMonth(const uint8_t& month) noexcept;

            /*!
            * @brief
            * Get abbreviated name of specified month.
            * 
            * @return
            * Abbreviated literal of provided month
            */
            std::string_view getMonthAbbrev(const uint8_t& month) noexcept;

            /*!
            * @brief
            * Determine day-of-week index of specified date.
            * 
            * @return
            * Day-of-week index of provided date
            */
            uint8_t getDayOfWeekIndex(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept;

            /*!
            * @brief
            * Determine day-of-week of specified date.
            * 
            * @return
            * Day-of-week literal of provided date
            */
            const char* getDayOfWeek(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept;

            /*!
            * @brief
            * Get abbreviated name of specified date
            * day-of-week.
            * 
            * @return
            * Abbreviated literal of date day-of-week
            */
            std::string_view getDayOfWeekAbbrev(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept;

            /*!
            * @brief
            * Convert Julian Day Number to Gregorian date.
            */
            void jdnToDate(const SimplyDt::JulianCalendar::JDN& jdn, SimplyDt::GregorianCalendar::Date& date) noexcept;

        }

    }

}



#endif // SIMPLYDT_L_SIMPLYDT_GREGORIAN_UTIL_H_
