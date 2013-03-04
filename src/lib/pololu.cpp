/***************************************************************************
 *   Copyright (C) 2010 by Ralf Kaestner and Luciano Spinello              *
 *   ralf.kaestner@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <libusb-1.0/libusb.h>

#include "utils.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

PololuUtils::ErrorPresets PololuUtils::errors;

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

PololuUtils::ErrorPresets::ErrorPresets() {
  (*this)[LIBUSB_SUCCESS] = "Success (no error)";
  (*this)[LIBUSB_ERROR_IO] = "Input/output error.";
  (*this)[LIBUSB_ERROR_INVALID_PARAM] = "Invalid parameter.";
  (*this)[LIBUSB_ERROR_ACCESS] = "Access denied (insufficient permissions)";
  (*this)[LIBUSB_ERROR_NO_DEVICE] =
    "No such device (it may have been disconnected)";
  (*this)[LIBUSB_ERROR_NOT_FOUND] = "Entity not found.";
  (*this)[LIBUSB_ERROR_BUSY] = "Resource busy.";
  (*this)[LIBUSB_ERROR_TIMEOUT] = "Operation timed out.";
  (*this)[LIBUSB_ERROR_OVERFLOW] = "Overflow.";
  (*this)[LIBUSB_ERROR_PIPE] = "Pipe error.";
  (*this)[LIBUSB_ERROR_INTERRUPTED] =
    "System call interrupted (perhaps due to signal)";
  (*this)[LIBUSB_ERROR_NO_MEM] = "Insufficient memory.";
  (*this)[LIBUSB_ERROR_NOT_SUPPORTED] =
    "Operation not supported or unimplemented on this platform.";
  (*this)[LIBUSB_ERROR_OTHER] = "Other error.";
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void PololuUtils::assert(const char* message, int err) {
  if (err)
#if LIBUSB_1_0_MINOR == 0 && LIBUSB_1_0_PATCH < 9
    PololuUtils:error(message, errors[err].c_str());
#else
    PololuUtils:error(message, libusb_error_name(error));
#endif
}
