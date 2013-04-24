cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  libpololu
  VERSION 0.1
  RELEASE alpha
  SUMMARY "Driver libraries for common Pololu motor controllers."
  AUTHOR "Ralf Kaestner"
  CONTACT "ralf.kaestner@gmail.com"
  HOME "http://github.com/kralf/libpololu"
  LICENSE "GNU Lesser General Public License (LGPL)"
  PREFIX pololu-
  INSTALL /usr
)

remake_doc(
  html
)

remake_pack_deb(
  DEPENDS libudev0[:a-z]* libusb-1.0-0[:a-z]* libxml[+][+]2.6-2
)
remake_pack_deb(
  COMPONENT utils
  DESCRIPTION "utilities"
  DEPENDS libpololu
)
remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "development headers"
  DEPENDS libpololu
)
remake_pack_deb(
  ARCH all
  COMPONENT doc
  DESCRIPTION "documentation"
)

remake_distribute_deb(
  DISTRIBUTION lucid
  SECTION libs
  UPLOAD ppa:kralf/asl
  DEPENDS remake libudev-dev libusb-1.0-0-dev libxml++2.6-dev pkg-config doxygen
  PASS CMAKE_BUILD_TYPE LIBPOLOLU_GIT_REVISION
)
remake_distribute_deb(
  DISTRIBUTION precise
  SECTION libs
  UPLOAD ppa:kralf/asl
  DEPENDS remake libudev-dev libusb-1.0-0-dev libxml++2.6-dev pkg-config doxygen
  PASS CMAKE_BUILD_TYPE LIBPOLOLU_GIT_REVISION
)
remake_distribute_deb(
  DISTRIBUTION precise
  ALIAS raspbian
  ARCH armhf
  SECTION libs
  UPLOAD ppa:kralf/naro
  DEPENDS remake libudev-dev libusb-1.0-0-dev libxml++2.6-dev pkg-config doxygen
  PASS CMAKE_BUILD_TYPE LIBPOLOLU_GIT_REVISION
  DEFINE LIBPOLOLU_EXTRA_CXX_FLAGS:STRING="-march=armv6 -mfpu=vfp -mfloat-abi=hard"
)
