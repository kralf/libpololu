string(REGEX REPLACE "[+]" "[+]" libxml_include "${LIBXML++_2_6_INCLUDE_DIRS}")
remake_include(${libxml_include})

remake_add_library(config LINK base ${LIBXML++_2_6_LIBRARIES})
remake_add_headers(INSTALL config)
