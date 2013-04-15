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

#include <limits>

#include "base/singleton.h"
#include "base/serializable.h"

#include "setmotorlimit.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::SetMotorLimit::Limits::Limits() {
  (*this)[limitMaxSpeed] = "MaxSpeed";
  (*this)[limitMaxAcceleration] = "MaxAcceleration";
  (*this)[limitMaxDeceleration] = "MaxDeceleration";
  (*this)[limitBrakeDuration] = "BrakeDuration";
}

Pololu::Smc::Usb::SetMotorLimit::Masks::Masks() {
  (*this)[maskForwardAndReverse] = "ForwardAndReverse";
  (*this)[maskForwardOnly] = "ForwardOnly";
  (*this)[maskReverseOnly] = "ReverseOnly";
}

Pololu::Smc::Usb::SetMotorLimit::Responses::Responses() {
  (*this)[responseSuccess] = "Success";
  (*this)[responseForwardConflict] = "ForwardConflict";
  (*this)[responseReverseConflict] = "ReverseConflict";
  (*this)[responseForwardAndReverseConflict] = "ForwardAndReverseConflict";
}

Pololu::Smc::Usb::SetMotorLimit::SetMotorLimit(Limit limit, Mask mask,
    unsigned short value) :
  Pololu::Usb::Request(typeVendor, 0x92, 0, limit | mask, 1) {
  setValue(value);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Smc::Usb::SetMotorLimit::Limit
    Pololu::Smc::Usb::SetMotorLimit::getLimit() const {
  return (Limit)(index & 0x03);
}

void Pololu::Smc::Usb::SetMotorLimit::setLimit(Limit limit) {
  index = getMask() | limit;
  setValue(getValue());
}

Pololu::Smc::Usb::SetMotorLimit::Mask
    Pololu::Smc::Usb::SetMotorLimit::getMask() const {
  return (Mask)(index & 0x0C);
}

void Pololu::Smc::Usb::SetMotorLimit::setMask(Mask mask) {
  index = getLimit() | mask;
}

unsigned short Pololu::Smc::Usb::SetMotorLimit::getValue() const {
  return value;
}

void Pololu::Smc::Usb::SetMotorLimit::setValue(unsigned short value) {
  if (getLimit() != limitBrakeDuration)
    ParameterRangeError::assert(value, 0, 3200);
  this->value = value;
}

Pololu::Smc::Usb::SetMotorLimit::Response
    Pololu::Smc::Usb::SetMotorLimit::getResponse() const {
  return (Response)data[0];
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Usb::SetMotorLimit* Pololu::Smc::Usb::SetMotorLimit::clone()
    const {
  return new SetMotorLimit(*this);
}

void Pololu::Smc::Usb::SetMotorLimit::read(std::istream& stream) {
  Serializable<Limit> limit;
  Serializable<Mask> mask;
  Serializable<size_t> value;

  setLimit(limit.read(stream, Singleton<Limits>::getInstance()));
  setMask(mask.read(stream, Singleton<Masks>::getInstance()));
  setValue(value.read(stream));
}

void Pololu::Smc::Usb::SetMotorLimit::write(std::ostream& stream) const {
  stream << Singleton<Responses>::getInstance()[getResponse()];
}
