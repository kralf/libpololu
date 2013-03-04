remake_include(${LIBUSB_1_0_INCLUDE_DIRS})

remake_add_library(usb LINK utils)
remake_add_headers(INSTALL usb)
