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

Pololu::Usc::Usb::Mini::GetSettings::GetSettings(unsigned char numChannels) :
  response(numChannels) {
}

Pololu::Usc::Usb::Mini::GetSettings::GetSettings(const GetSettings& src) :
  Pololu::Usc::Usb::GetSettings(src),
  response(src.response) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Usc::Usb::Mini::Settings&
    Pololu::Usc::Usb::Mini::GetSettings::getResponse() {
  return response;
}

const Pololu::Usc::Usb::Mini::Settings&
    Pololu::Usc::Usb::Mini::GetSettings::getResponse() const {
  return response;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::Mini::GetSettings*
    Pololu::Usc::Usb::Mini::GetSettings::clone() const {
  return new GetSettings(*this);
}

void Pololu::Usc::Usb::Mini::GetSettings::transfer(libusb_device_handle*
    handle, std::vector<unsigned char>& data, double timeout) {
  Pololu::Usc::Usb::GetSettings::transfer(handle, data, timeout);

  response.servoMultiplier = transfer<unsigned char>(handle, 0x1A, timeout)+1;
  response.servoPeriod = (transfer<unsigned short>(handle, 0x13, timeout) << 8);
  response.servoPeriod |= transfer<unsigned char>(handle, 0x12, timeout);

  if (response.channels.size() > 18)
    response.enablePullups = transfer<unsigned char>(handle, 0x15, timeout);
  else
    response.enablePullups = false;

  std::vector<unsigned char> channelModeBytes(6);
  for (int i = 0; i < channelModeBytes.size(); ++i)
    channelModeBytes[i] = transfer<unsigned char>(handle, 0x0C+i, timeout);
  for (int i = 0; i < response.channels.size(); ++i)
    response.channels[i].mode = (Settings::Channel::Mode)(
      (channelModeBytes[i >> 2] >> ((i & 3) << 1)) & 3);
}
