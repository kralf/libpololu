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

Pololu::Usc::Usb::Micro::GetSettings::GetSettings() {
}

Pololu::Usc::Usb::Micro::GetSettings::GetSettings(const GetSettings& src) :
  Pololu::Usc::Usb::GetSettings(src),
  response(src.response) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Usc::Usb::Micro::Settings&
    Pololu::Usc::Usb::Micro::GetSettings::getResponse() {
  return response;
}

const Pololu::Usc::Usb::Micro::Settings&
    Pololu::Usc::Usb::Micro::GetSettings::getResponse() const {
  return response;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::Micro::GetSettings*
    Pololu::Usc::Usb::Micro::GetSettings::clone() const {
  return new GetSettings(*this);
}

void Pololu::Usc::Usb::Micro::GetSettings::transfer(libusb_device_handle*
    handle, std::vector<unsigned char>& data, double timeout) {
  Pololu::Usc::Usb::GetSettings::transfer(handle, data, timeout);

  response.servosAvailable = transfer<unsigned char>(handle, 0x01, timeout);
  response.servoPeriod = transfer<unsigned char>(handle, 0x02, timeout);

  unsigned char ioMask = transfer<unsigned char>(handle, 0x10, timeout);
  unsigned char outputMask = transfer<unsigned char>(handle, 0x11, timeout);
  for (int i = 0; i < response.channels.size(); ++i) {
    unsigned char bitMask = (1 << Settings::channelToPort(i));

    if (!(ioMask & bitMask))
      response.channels[i].mode = Settings::Channel::modeServo;
    else if (!(outputMask & bitMask))
      response.channels[i].mode = Settings::Channel::modeInput;
    else
      response.channels[i].mode = Settings::Channel::modeOutput;
  }
}
