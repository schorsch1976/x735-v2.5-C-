#######################################################################
# gpio
#######################################################################
if(UNIX)
	add_library(Gpio	INTERFACE IMPORTED GLOBAL)

	find_package(PkgConfig)
	## use pkg-config to get hints for gpiodcxx locations
	pkg_check_modules(PC_Gpio QUIET gpiodcxx)

	## use the hint from about to find the location of libsodium
	find_path(Gpio_INCLUDE_DIR
			NAMES gpiod.hpp
			PATHS ${PC_Gpio_INCLUDE_DIRS}
			)

	## use the hint from about to find the location of sodium
	find_library(Gpio_LIBRARY
			NAMES gpiodcxx
			PATHS ${PC_Gpio_LIBRARY_DIRS}
			)

	target_include_directories(	Gpio	INTERFACE ${Gpio_INCLUDE_DIR})
	target_link_libraries(		Gpio	INTERFACE ${Gpio_LIBRARY})
endif()
