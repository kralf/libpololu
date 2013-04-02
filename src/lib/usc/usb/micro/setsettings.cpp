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

Pololu::Usc::Usb::Micro::SetSettings::SetSettings(const Settings& settings) :
  settings(settings) {
}

Pololu::Usc::Usb::Micro::SetSettings::SetSettings(const SetSettings& src) :
  Pololu::Usc::Usb::SetSettings(src),
  settings(src.settings) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const Pololu::Usc::Usb::Micro::Settings&
    Pololu::Usc::Usb::Micro::SetSettings::getSettings() const {
  return settings;
}

void Pololu::Usc::Usb::Micro::SetSettings::setSettings(const Settings&
    settings) {
  this->settings = settings;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::Micro::SetSettings*
    Pololu::Usc::Usb::Micro::SetSettings::clone() const {
  return new SetSettings(*this);
}

void Pololu::Usc::Usb::Micro::SetSettings::read(std::istream& stream) {
  Settings settings;
  stream >> settings;

  setSettings(settings);
}

void Pololu::Usc::Usb::Micro::SetSettings::transfer(libusb_device_handle*
    handle, std::vector<unsigned char>& data, double timeout) {
  Pololu::Usc::Usb::SetSettings::transfer(handle, data, timeout);

  transfer(handle, 0x01, settings.servosAvailable, timeout);
  transfer(handle, 0x02, settings.servoPeriod, timeout);

  unsigned char ioMask = 0;
  unsigned char outputMask = 0;
  for (int i = 0; i < settings.channels.size(); ++i) {
    unsigned char bitMask = (1 << Settings::channelToPort(i));

    if ((settings.channels[i].mode == Settings::Channel::modeInput) ||
        (settings.channels[i].mode == Settings::Channel::modeOutput))
      ioMask |= (1 << Settings::channelToPort(i));
    if (settings.channels[i].mode == Settings::Channel::modeOutput)
      outputMask |= (1 << Settings::channelToPort(i));
  }
  transfer(handle, 0x10, ioMask, timeout);
  transfer(handle, 0x11, outputMask, timeout);
}
