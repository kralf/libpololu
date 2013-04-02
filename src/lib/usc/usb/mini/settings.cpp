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

#include "config/section.h"

#include "settings.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::Mini::Settings::Settings(unsigned char numChannels) :
  Pololu::Usc::Usb::Settings(numChannels),
  servoMultiplier(1),
  servoPeriod(80000),
  enablePullups(false) {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Usc::Usb::Mini::Settings::read(const Configuration::Section&
    section) {
  Pololu::Usc::Usb::Settings::read(section);

  section.query("Channels/ServoMultiplier", servoMultiplier);
  section.query("Channels/MiniMaestroServoPeriod", servoPeriod);
  if (channels.size() > 18)
    section.query("Channels/EnablePullups", enablePullups);
}

void Pololu::Usc::Usb::Mini::Settings::write(Configuration::Section& section)
    const {
  Pololu::Usc::Usb::Settings::write(section);

  section["Channels/ServoMultiplier"] = servoMultiplier;
  section["Channels/MiniMaestroServoPeriod"] = servoPeriod;
  if (channels.size() > 18)
    section["Channels/EnablePullups"] = enablePullups;
}
