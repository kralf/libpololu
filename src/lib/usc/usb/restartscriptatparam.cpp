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

#include "base/serializable.h"

#include "restartscriptatparam.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::RestartScriptAtParam::RestartScriptAtParam(unsigned char
    subroutine, short parameter) :
  Pololu::Usb::Request(typeVendor, 0xA4, parameter, subroutine) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char Pololu::Usc::Usb::RestartScriptAtParam::getSubroutine() const {
  return index;
}

void Pololu::Usc::Usb::RestartScriptAtParam::setSubroutine(unsigned char
    subroutine) {
  index = subroutine;
}

short Pololu::Usc::Usb::RestartScriptAtParam::getParameter() const {
  return value;
}

void Pololu::Usc::Usb::RestartScriptAtParam::setParameter(short parameter) {
  value = parameter;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::RestartScriptAtParam*
    Pololu::Usc::Usb::RestartScriptAtParam::clone() const {
  return new RestartScriptAtParam(*this);
}

void Pololu::Usc::Usb::RestartScriptAtParam::read(std::istream& stream) {
  Serializable<unsigned char> subroutine;
  Serializable<short> parameter;

  setParameter(parameter.read(stream));
  setSubroutine(subroutine.read(stream));
}
