/***************************************************************************
 *   Copyright (C) 2013 by Ralf Kaestner                                   *
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

#include "setsettings.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::SetSettings::SetSettings(const Settings& settings) :
  Pololu::Usb::Request(typeVendor, 0x82, 0, 0) {
  setSettings(settings);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Smc::Usb::Settings Pololu::Smc::Usb::SetSettings::getSettings()
    const {
  return reinterpret_cast<const Settings&>(data[0]);
}

void Pololu::Smc::Usb::SetSettings::setSettings(const Settings& settings) {
  const unsigned char* data =
    reinterpret_cast<const unsigned char*>(&settings);
  this->data.assign(data, data+sizeof(Settings));
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Usb::SetSettings* Pololu::Smc::Usb::SetSettings::clone() const {
  return new SetSettings(*this);
}

void Pololu::Smc::Usb::SetSettings::read(std::istream& stream) {
  Settings settings;
  stream >> settings;

  setSettings(settings);
}
