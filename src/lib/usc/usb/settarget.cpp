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

#include "settarget.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::SetTarget::SetTarget(unsigned char numServos, unsigned char
    servo, unsigned short value) :
  Pololu::Usb::Request(typeVendor, 0x85, value, 0),
  numServos(numServos) {
  setServo(servo);
}

Pololu::Usc::Usb::SetTarget::SetTarget(const SetTarget& src) :
  Pololu::Usb::Request(src),
  numServos(src.numServos) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char Pololu::Usc::Usb::SetTarget::getServo() const {
  return index;
}

void Pololu::Usc::Usb::SetTarget::setServo(unsigned char servo) {
  ParameterRangeError::assert(servo, 0, numServos);
  index = servo;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::SetTarget* Pololu::Usc::Usb::SetTarget::clone() const {
  return new SetTarget(*this);
}

void Pololu::Usc::Usb::SetTarget::read(std::istream& stream) {
  Serializable<unsigned char> servo;
  Serializable<unsigned short> value;

  setServo(servo.read(stream));
  setValue(value.read(stream));
}
