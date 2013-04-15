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

#include "config/section.h"

#include "settings.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::Micro::Settings::Settings() :
  Pololu::Usc::Usb::Settings(6),
  servosAvailable(6),
  servoPeriod(156) {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Usc::Usb::Micro::Settings::read(const Configuration::Section&
    section) {
  Pololu::Usc::Usb::Settings::read(section);

  section.query("Channels/ServosAvailable", servosAvailable);
  section.query("Channels/ServoPeriod", servoPeriod);
}

void Pololu::Usc::Usb::Micro::Settings::write(Configuration::Section& section)
    const {
  Pololu::Usc::Usb::Settings::write(section);

  section["Channels/ServosAvailable"] = servosAvailable;
  section["Channels/ServoPeriod"] = servoPeriod;
}

unsigned char Pololu::Usc::Usb::Micro::Settings::channelToPort(unsigned char
    channel) {
  if (channel <= 3)
    return channel;
  else if (channel < 6)
    return channel+2;
  else
    throw ChannelError(channel);
}
