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

Pololu::Usc::Usb::Mini::SetSettings::SetSettings(unsigned char numChannels) :
  settings(numChannels) {
}

Pololu::Usc::Usb::Mini::SetSettings::SetSettings(const SetSettings& src) :
  Pololu::Usc::Usb::SetSettings(src),
  settings(src.settings) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const Pololu::Usc::Usb::Mini::Settings&
    Pololu::Usc::Usb::Mini::SetSettings::getSettings() const {
  return settings;
}

void Pololu::Usc::Usb::Mini::SetSettings::setSettings(const Settings&
    settings) {
  this->settings = settings;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::Mini::SetSettings*
    Pololu::Usc::Usb::Mini::SetSettings::clone() const {
  return new SetSettings(*this);
}

void Pololu::Usc::Usb::Mini::SetSettings::read(std::istream& stream) {
  Settings settings(this->settings.channels.size());
  stream >> settings;

  setSettings(settings);
}

void Pololu::Usc::Usb::Mini::SetSettings::transfer(libusb_device_handle*
    handle, std::vector<unsigned char>& data, double timeout) {
  Pololu::Usc::Usb::SetSettings::transfer(handle, data, timeout);

  unsigned char multiplier = 0;
  if (settings.servoMultiplier > 256)
    multiplier = 255;
  else if (settings.servoMultiplier >= 1)
    multiplier = settings.servoMultiplier-1;

  transfer(handle, 0x1A, multiplier, timeout);
  transfer<unsigned short>(handle, 0x13, settings.servoPeriod >> 8, timeout);
  transfer<unsigned char>(handle, 0x12, settings.servoPeriod & 0xFF, timeout);

  if (settings.channels.size() > 18)
    transfer<unsigned char>(handle, 0x15, settings.enablePullups, timeout);

  std::vector<unsigned char> channelModeBytes(6);
  for (int i = 0; i < settings.channels.size(); ++i)
    channelModeBytes[i >> 2] |= settings.channels[i].mode << ((i & 3) << 1);
  for (int i = 0; i < channelModeBytes.size(); ++i)
    transfer(handle, 0x0C+i, channelModeBytes[i], timeout);
}
