remake_project_header(config.h.remake)
remake_include()

remake_add_directories()

remake_add_library(pololu PREFIX OFF LINK command
  FORCE_LINK usb serial smc usc)
remake_add_headers()
remake_pkg_config_generate()
