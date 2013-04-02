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

#include "config/document.h"

#include "variables.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::Mini::Variables::PerformanceErrors::PerformanceErrors() {
  (*this)[performanceErrorNone] = "None";
  (*this)[performanceErrorAdvancedUpdate] = "AdvancedUpdate";
  (*this)[performanceErrorBasicUpdate] = "BasicUpdate";
  (*this)[performanceErrorPeriod] = "Period";
}

Pololu::Usc::Usb::Mini::Variables::Variables() :
  scriptStatus(Device::scriptStatusRunning),
  performanceErrorOccurred(performanceErrorNone) {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Usc::Usb::Mini::Variables::write(std::ostream& stream) const {
  Pololu::Configuration::Document document("UscVariables");

  Pololu::Usc::Usb::Variables::write(document);

  document["ScriptStatus"] = Singleton<Device::ScriptStatuses>::getInstance()[
    (Device::ScriptStatus)scriptStatus];
  for (int i = 0; i <= 2; ++i)
  document["PerformanceErrorOccurred/"+
    Singleton<PerformanceErrors>::getInstance()[(PerformanceError)(1 << i)]] =
      (bool)(performanceErrorOccurred & (1 << i));

  document.write(stream);
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Usc::Usb::Mini::Variables& variables) {
  variables.write(stream);
  return stream;
}
