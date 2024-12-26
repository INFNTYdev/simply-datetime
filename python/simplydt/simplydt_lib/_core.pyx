
from . cimport _core as sdtlib


"""
Namespace: SimplyDt::GregorianCalendar::Util
"""
def is_valid_year(year: int) -> bool:
    """ Validate provided year. """
    # Check integer range here...
    return sdtlib.isValidYear(<uint16_t>year)
