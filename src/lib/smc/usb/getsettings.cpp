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

#include "getsettings.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::GetSettings::GetSettings() :
  Pololu::Usb::Request(typeVendor, 0x81, 0, 0, sizeof(Settings)) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Smc::Usb::Settings Pololu::Smc::Usb::GetSettings::getResponse()
    const {
  return reinterpret_cast<const Settings&>(data[0]);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Usb::GetSettings* Pololu::Smc::Usb::GetSettings::clone() const {
  return new GetSettings(*this);
}

void Pololu::Smc::Usb::GetSettings::write(std::ostream& stream) const {
  stream << getResponse();
}
