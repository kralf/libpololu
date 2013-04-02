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

#include "setscriptstatus.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::SetScriptStatus::SetScriptStatus(Device::ScriptStatus
    status) :
  Pololu::Usb::Request(typeVendor, 0xA2, status, 0) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Usc::Device::ScriptStatus
    Pololu::Usc::Usb::SetScriptStatus::getStatus() const {
  return (Device::ScriptStatus)value;
}

void Pololu::Usc::Usb::SetScriptStatus::setStatus(Device::ScriptStatus
    status) {
  value = status;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::SetScriptStatus*
    Pololu::Usc::Usb::SetScriptStatus::clone() const {
  return new SetScriptStatus(*this);
}

void Pololu::Usc::Usb::SetScriptStatus::read(std::istream& stream) {
  Serializable<Device::ScriptStatus> status;
  setStatus(status.read(stream,
    Singleton<Device::ScriptStatuses>::getInstance()));
}
