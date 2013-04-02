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

Pololu::Usc::Usb::GetSettings::GetSettings() :
  Pololu::Usb::Request(typeVendor, 0x81, 0, 0, 0) {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Usc::Usb::GetSettings::write(std::ostream& stream) const {
  stream << getResponse();
}

void Pololu::Usc::Usb::GetSettings::transfer(libusb_device_handle*
    handle, std::vector<unsigned char>& data, double timeout) {
  Settings& response = getResponse();

  response.serialMode = (Settings::SerialMode)transfer<unsigned char>(
    handle, 0x03, timeout);
  response.fixedBaudRateRegister = transfer<unsigned short>(handle,
    0x04, timeout);
  response.enableCrc = transfer<unsigned char>(handle, 0x08, timeout);
  response.neverSuspend = transfer<unsigned char>(handle, 0x09, timeout);
  response.serialDeviceNumber = transfer<unsigned char>(handle, 0x0A, timeout);
  response.serialMiniSscOffset = transfer<unsigned char>(handle, 0x19,
    timeout);
  response.serialTimeout = transfer<unsigned short>(handle, 0x06, timeout);
  response.scriptStatus = (Device::ScriptStatus)transfer<unsigned char>(
    handle, 0x18, timeout);

  for (int i = 0; i < response.channels.size(); ++i) {
    unsigned short home = transfer<unsigned short>(handle, (0x1E)+i*9,
      timeout);
    if (home == 0) {
      response.channels[i].homeMode = Settings::Channel::homeModeOff;
      response.channels[i].home = 0;
    }
    else if (home == 1) {
      response.channels[i].homeMode = Settings::Channel::homeModeIgnore;
      response.channels[i].home = 0;
    }
    else {
      response.channels[i].homeMode = Settings::Channel::homeModeGoto;
      response.channels[i].home = home;
    }

    response.channels[i].minimum = 64*transfer<unsigned char>(handle,
      0x20+i*9, timeout);
    response.channels[i].maximum = 64*transfer<unsigned char>(handle,
      0x21+i*9, timeout);
    response.channels[i].neutral = transfer<unsigned short>(handle,
      0x22+i*9, timeout);
    response.channels[i].range = 127*transfer<unsigned char>(handle,
      0x24+i*9, timeout);
    response.channels[i].speed = Device::expSpeedToSpeed(
      transfer<unsigned char>(handle, 0x25+i*9, timeout));
    response.channels[i].acceleration = transfer<unsigned char>(handle,
      0x26+i*9, timeout);
  }
}
