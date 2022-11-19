set(TARGET	x735-fanspeed)

#######################################################################
# Executable
#######################################################################
add_executable(${TARGET})

target_sources(${TARGET}
	PRIVATE
			main.cpp
)

#######################################################################
# Libraries
#######################################################################
target_link_libraries(${TARGET}
	Gpio
	pthread
)

install(TARGETS			${TARGET}	RUNTIME	DESTINATION bin)
