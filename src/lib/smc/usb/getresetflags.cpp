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

#include "base/singleton.h"

#include "getresetflags.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::GetResetFlags::Responses::Responses() {
  (*this)[responseResetPin] = "ResetPin";
  (*this)[responsePower] = "Power";
  (*this)[responseSoftware] = "Software";
  (*this)[responseWatchdog] = "Watchdog";
}

Pololu::Smc::Usb::GetResetFlags::GetResetFlags() :
  Pololu::Usb::Request(typeVendor, 0x85, 0, 0, 1) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Smc::Usb::GetResetFlags::Response
    Pololu::Smc::Usb::GetResetFlags::getResponse() const {
  return (Response)data[0];
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Usb::GetResetFlags* Pololu::Smc::Usb::GetResetFlags::clone()
    const {
  return new GetResetFlags(*this);
}

void Pololu::Smc::Usb::GetResetFlags::write(std::ostream& stream) const {
  stream << Singleton<Responses>::getInstance()[getResponse()];
}
