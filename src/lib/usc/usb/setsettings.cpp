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

#include "setsettings.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::SetSettings::SetSettings() :
  Pololu::Usb::Request(typeVendor, 0x82, 0, 0) {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Usc::Usb::SetSettings::transfer(libusb_device_handle*
    handle, std::vector<unsigned char>& data, double timeout) {
  const Settings& settings = getSettings();

  transfer<unsigned char>(handle, 0x03, settings.serialMode, timeout);
  transfer(handle, 0x04, settings.fixedBaudRateRegister, timeout);
  transfer<unsigned char>(handle, 0x08, settings.enableCrc, timeout);
  transfer<unsigned char>(handle, 0x09, settings.neverSuspend, timeout);
  transfer(handle, 0x0A, settings.serialDeviceNumber, timeout);
  transfer(handle, 0x19, settings.serialMiniSscOffset, timeout);
  transfer(handle, 0x06, settings.serialTimeout, timeout);
  transfer<unsigned char>(handle, 0x18, settings.scriptStatus, timeout);

  for (int i = 0; i < settings.channels.size(); ++i) {
    Settings::Channel::HomeMode homeMode = settings.channels[i].homeMode;
    if (settings.channels[i].mode == Settings::Channel::modeInput)
      homeMode = Settings::Channel::homeModeIgnore;

    unsigned short home = settings.channels[i].home;
    if (homeMode == Settings::Channel::homeModeOff)
      home = 0;
    else if (homeMode == Settings::Channel::homeModeIgnore)
      home = 1;
    transfer(handle, (0x1E)+i*9, home, timeout);

    transfer<unsigned char>(handle, 0x20+i*9, settings.channels[i].minimum/64,
      timeout);
    transfer<unsigned char>(handle, 0x21+i*9, settings.channels[i].maximum/64,
      timeout);
    transfer(handle, 0x22+i*9, settings.channels[i].neutral, timeout);
    transfer<unsigned char>(handle, 0x24+i*9, settings.channels[i].range/127,
      timeout);
    transfer<unsigned char>(handle, 0x25+i*9, Device::speedToExpSpeed(
      settings.channels[i].speed), timeout);
    transfer(handle, 0x26+i*9, settings.channels[i].acceleration, timeout);
  }
}
