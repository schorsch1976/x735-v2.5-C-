#######################################################################
# Boost
#######################################################################

find_package(Boost 1.67.0 COMPONENTS
	system

		REQUIRED)

if ( Boost_FOUND )
	set(CFLAGS
			BOOST_ALL_DYN_LINK=1
	)

	set_target_properties(Boost::boost
		Boost::system
			PROPERTIES INTERFACE_LINK_DIRECTORIES "${BOOST_LIBRARYDIR}"
	)
	set_target_properties( Boost::boost
		Boost::system
			PROPERTIES INTERFACE_COMPILE_DEFINITIONS "${CFLAGS}" 
	)

	set_target_properties( Boost::boost
		Boost::system
			PROPERTIES IMPORTED_GLOBAL TRUE
	)

endif ()
