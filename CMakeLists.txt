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
)
remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "development headers"
)
remake_pack_deb(
  ARCH all
  COMPONENT doc
  DESCRIPTION "documentation"
)
