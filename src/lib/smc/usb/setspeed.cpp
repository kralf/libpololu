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

#include "setspeed.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::SetSpeed::Directions::Directions() {
  (*this)[directionForward] = "Forward";
  (*this)[directionReverse] = "Reverse";
}

Pololu::Smc::Usb::SetSpeed::SetSpeed(int value) :
  Pololu::Usb::Request(typeVendor, 0x90, 0, directionForward) {
  setValue(value);
}

Pololu::Smc::Usb::SetSpeed::SetSpeed(unsigned short value, Direction
    direction) :
  Pololu::Usb::Request(typeVendor, 0x90, 0, direction) {
  setValue(value, direction);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

int Pololu::Smc::Usb::SetSpeed::getValue() const {
  if (index == directionForward)
    return value;
  else
    return -value;
}

void Pololu::Smc::Usb::SetSpeed::setValue(int value) {
  if (value < 0)
    setValue(-value, directionReverse);
  else
    setValue(value, directionForward);
}

void Pololu::Smc::Usb::SetSpeed::setValue(unsigned short value, Direction
    direction) {
  ParameterRangeError::assert(value, 0, 3200);

  this->value = value;
  index = direction;
}

Pololu::Smc::Usb::SetSpeed::Direction
    Pololu::Smc::Usb::SetSpeed::getDirection() const {
  return (Direction)index;
}

void Pololu::Smc::Usb::SetSpeed::setDirection(Direction direction) {
  index = direction;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Usb::SetSpeed* Pololu::Smc::Usb::SetSpeed::clone() const {
  return new SetSpeed(*this);
}

void Pololu::Smc::Usb::SetSpeed::read(std::istream& stream) {
  Serializable<int> value;
  setValue(value.read(stream));
}
