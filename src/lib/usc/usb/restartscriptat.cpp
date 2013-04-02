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

#include "restartscriptat.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::RestartScriptAt::RestartScriptAt(unsigned char
    subroutine) :
  Pololu::Usb::Request(typeVendor, 0xA3, 0, subroutine) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char Pololu::Usc::Usb::RestartScriptAt::getSubroutine() const {
  return index;
}

void Pololu::Usc::Usb::RestartScriptAt::setSubroutine(unsigned char
    subroutine) {
  index = subroutine;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::RestartScriptAt* Pololu::Usc::Usb::RestartScriptAt::clone()
    const {
  return new RestartScriptAt(*this);
}

void Pololu::Usc::Usb::RestartScriptAt::read(std::istream& stream) {
  Serializable<unsigned char> subroutine;
  setSubroutine(subroutine.read(stream));
}
