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

#include <cstring>

#include "config/document.h"

#include "variables.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::Micro::Variables::Variables() :
  scriptStatus(Device::scriptStatusRunning),
  reserved1(0) {
  memset(reserved0, 0, sizeof(reserved0));
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Usc::Usb::Micro::Variables::write(std::ostream& stream) const {
  Pololu::Configuration::Document document("UscVariables");

  Pololu::Usc::Usb::Variables::write(document);
  document["ScriptStatus"] = Singleton<Device::ScriptStatuses>::getInstance()[
    (Device::ScriptStatus)scriptStatus];

  Pololu::Usc::Usb::Variables::Stack stack(32, this->stack);
  stack.write(document, stackPointer);
  Pololu::Usc::Usb::Variables::CallStack callStack(10, this->callStack);
  callStack.write(document, callStackPointer);
  Pololu::Usc::Usb::Variables::Servos servos(6, this->servos);
  servos.write(document);

  document.write(stream);
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Usc::Usb::Micro::Variables& variables) {
  variables.write(stream);
  return stream;
}
