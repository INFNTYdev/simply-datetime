
# \src\ DIRECTORY CMAKE SCRIPT


# Library Build
add_library(
	simplydtlib
	"common/julian_date_system/jdn_util.cpp"
	"common/gregorian_calendar/gregorian_util.cpp"
)
