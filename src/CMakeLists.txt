
#============================#
#   \src\ Directory Script   #
#============================#



add_library(
	simplydtlib
	"common/julian_date_system/jdn_util.cpp"
	"common/gregorian_calendar/gregorian_util.cpp"
	"common/coord_universal_time/utc_util.cpp"
	"duration/duration.cpp"
	"datetime/datetime.cpp"
)

target_include_directories(
	simplydtlib

	PUBLIC
	"${CMAKE_SOURCE_DIR}/include"
)

message(STATUS "SDT INCLUDE: ${CMAKE_SOURCE_DIR}/include")
