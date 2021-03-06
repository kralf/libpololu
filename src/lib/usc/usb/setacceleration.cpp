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

#include "base/serializable.h"

#include "setacceleration.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::SetAcceleration::SetAcceleration(unsigned char numServos,
    unsigned char servo, unsigned short value) :
  Pololu::Usb::Request(typeVendor, 0x84, value, 0 | 0x80),
  numServos(numServos) {
  setServo(servo);
}

Pololu::Usc::Usb::SetAcceleration::SetAcceleration(const SetAcceleration&
    src) :
  Pololu::Usb::Request(src),
  numServos(src.numServos) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char Pololu::Usc::Usb::SetAcceleration::getServo() const {
  return index;
}

void Pololu::Usc::Usb::SetAcceleration::setServo(unsigned char servo) {
  ParameterRangeError::assert(servo, 0, numServos);
  index = servo | 0x80;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::SetAcceleration* Pololu::Usc::Usb::SetAcceleration::clone()
    const {
  return new SetAcceleration(*this);
}

void Pololu::Usc::Usb::SetAcceleration::read(std::istream& stream) {
  Serializable<unsigned char> servo;
  Serializable<unsigned short> value;

  setServo(servo.read(stream));
  setValue(value.read(stream));
}
