
#==================================
#     /tests Directory Script
#==================================



if(UNIT_TESTING)
	add_subdirectory(unit)
endif()

if(CLI_DEBUGGING)
	add_subdirectory(cli)
endif()

