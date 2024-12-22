
#==================================
#     /tests Directory Script
#==================================



if(UNIT_TESTING)
	add_subdirectory(unit)
	add_subdirectory(benchmark)
endif()

if(CLI_DEBUGGING)
	add_subdirectory(cli)
endif()

