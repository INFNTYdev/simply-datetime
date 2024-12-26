
"""
     Core Simply Datetime Library Bindings

     Exposes:
     SimplyDt::GregorianCalendar::Util
"""


from libcpp cimport bool
from libc.stdint cimport uint16_t


"""
Namespace: SimplyDt::GregorianCalendar::Util
"""
cdef extern from "simplydt/gregorian_calendar/gregorian_util.hpp" namespace "SimplyDt::GregorianCalendar::Util":
    bool isValidYear(const uint16_t& year) noexcept nogil
