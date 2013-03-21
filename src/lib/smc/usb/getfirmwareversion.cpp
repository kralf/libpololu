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

#include "getfirmwareversion.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::GetFirmwareVersion::GetFirmwareVersion() :
  Pololu::Usb::Request(typeStandard, 0x06, 0x0100, 0, 14) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Device::FirmwareVersion
    Pololu::Smc::Usb::GetFirmwareVersion::getResponse() const {
  size_t major = (data[13] & 0xF)+(data[13] >> 4 & 0xF)*10;
  size_t minor = (data[12] & 0xF)+(data[12] >> 4 & 0xF)*10;

  return Pololu::Device::FirmwareVersion(major, minor);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Usb::GetFirmwareVersion*
    Pololu::Smc::Usb::GetFirmwareVersion::clone() const {
  return new GetFirmwareVersion(*this);
}

void Pololu::Smc::Usb::GetFirmwareVersion::write(std::ostream& stream) const {
  stream << getResponse();
}
