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

#include <libusb.h>

#include "base/singleton.h"

#include "error.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::USB::Error::Descriptions::Descriptions() {
  (*this)[LIBUSB_SUCCESS] = "Success.";
  (*this)[LIBUSB_ERROR_IO] = "Input/output error.";
  (*this)[LIBUSB_ERROR_INVALID_PARAM] = "Invalid parameter.";
  (*this)[LIBUSB_ERROR_ACCESS] = "Access denied.";
  (*this)[LIBUSB_ERROR_NO_DEVICE] = "No such device.";
  (*this)[LIBUSB_ERROR_NOT_FOUND] = "Entity not found.";
  (*this)[LIBUSB_ERROR_BUSY] = "Resource busy.";
  (*this)[LIBUSB_ERROR_TIMEOUT] = "Operation timed out.";
  (*this)[LIBUSB_ERROR_OVERFLOW] = "Overflow.";
  (*this)[LIBUSB_ERROR_PIPE] = "Pipe error.";
  (*this)[LIBUSB_ERROR_INTERRUPTED] = "System call interrupted.";
  (*this)[LIBUSB_ERROR_NO_MEM] = "Insufficient memory.";
  (*this)[LIBUSB_ERROR_NOT_SUPPORTED] = "Operation not supported.";
  (*this)[LIBUSB_ERROR_OTHER] = "Other error.";
}

Pololu::USB::Error::Error(int error) :
  Exception("USB error: %s",
    Singleton<Descriptions>::getInstance()[error].c_str()) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

std::string Pololu::USB::Error::Descriptions::operator[](int error) const {
  const_iterator it = find(error);
  if (it != end())
    return it->second;
  else
    return "Unkown error.";
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::USB::Error::assert(int error) {
  if (error != LIBUSB_SUCCESS)
    throw Error(error);
}
