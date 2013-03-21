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

#include "base/serializable.h"

#include "setusbkill.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::SetUsbKill::SetUsbKill(bool active) :
  Pololu::Usb::Request(typeVendor, 0x93, active, 0) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

bool Pololu::Smc::Usb::SetUsbKill::getActive() const {
  return value;
}

void Pololu::Smc::Usb::SetUsbKill::setActive(bool active) {
  value = active;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Usb::SetUsbKill* Pololu::Smc::Usb::SetUsbKill::clone() const {
  return new SetUsbKill(*this);
}

void Pololu::Smc::Usb::SetUsbKill::read(std::istream& stream) {
  Serializable<bool> active;
  setActive(active.read(stream));
}
