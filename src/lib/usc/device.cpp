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

#include "device.h"

#include "usb/protocol.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

const size_t Pololu::Usc::Device::instructionFrequency = 12000000;

Pololu::Usc::Device::Prototypes Pololu::Usc::Device::prototypes;

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Device::Types::Types() {
  (*this)[typeMaestro6] = "Maestro6";
  (*this)[typeMaestro6b] = "Maestro6b";
  (*this)[typeMaestro12] = "Maestro12";
  (*this)[typeMaestro12b] = "Maestro12b";
  (*this)[typeMaestro18] = "Maestro18";
  (*this)[typeMaestro18b] = "Maestro18b";
  (*this)[typeMaestro24] = "Maestro24";
  (*this)[typeMaestro24b] = "Maestro24b";
}

Pololu::Usc::Device::SuperTypes::SuperTypes() {
  (*this)[typeMaestro6] = superTypeMicro;
  (*this)[typeMaestro6b] = superTypeMicro;
  (*this)[typeMaestro12] = superTypeMini;
  (*this)[typeMaestro12b] = superTypeMini;
  (*this)[typeMaestro18] = superTypeMini;
  (*this)[typeMaestro18b] = superTypeMini;
  (*this)[typeMaestro24] = superTypeMini;
  (*this)[typeMaestro24b] = superTypeMini;
}

Pololu::Usc::Device::StackSizes::StackSizes() {
  (*this)[typeMaestro6] = 32;
  (*this)[typeMaestro6b] = 32;
  (*this)[typeMaestro12] = 126;
  (*this)[typeMaestro12b] = 126;
  (*this)[typeMaestro18] = 126;
  (*this)[typeMaestro18b] = 126;
  (*this)[typeMaestro24] = 126;
  (*this)[typeMaestro24b] = 126;
}

Pololu::Usc::Device::CallStackSizes::CallStackSizes() {
  (*this)[typeMaestro6] = 10;
  (*this)[typeMaestro6b] = 10;
  (*this)[typeMaestro12] = 126;
  (*this)[typeMaestro12b] = 126;
  (*this)[typeMaestro18] = 126;
  (*this)[typeMaestro18b] = 126;
  (*this)[typeMaestro24] = 126;
  (*this)[typeMaestro24b] = 126;
}

Pololu::Usc::Device::NumChannels::NumChannels() {
  (*this)[typeMaestro6] = 6;
  (*this)[typeMaestro6b] = 6;
  (*this)[typeMaestro12] = 12;
  (*this)[typeMaestro12b] = 12;
  (*this)[typeMaestro18] = 18;
  (*this)[typeMaestro18b] = 18;
  (*this)[typeMaestro24] = 24;
  (*this)[typeMaestro24b] = 24;
}

Pololu::Usc::Device::MaxScriptSizes::MaxScriptSizes() {
  (*this)[typeMaestro6] = 1024;
  (*this)[typeMaestro6b] = 1024;
  (*this)[typeMaestro12] = 8192;
  (*this)[typeMaestro12b] = 8192;
  (*this)[typeMaestro18] = 8192;
  (*this)[typeMaestro18b] = 8192;
  (*this)[typeMaestro24] = 8192;
  (*this)[typeMaestro24b] = 8192;
}

Pololu::Usc::Device::ScriptStatuses::ScriptStatuses() {
  (*this)[scriptStatusRunning] = "Running";
  (*this)[scriptStatusStopped] = "Stopped";
}

Pololu::Usc::Device::Prototypes::Prototypes() {
  for (std::map<Type, std::string>::const_iterator
      it = Singleton<Types>::getInstance().begin();
      it != Singleton<Types>::getInstance().end(); ++it)
    push_back(Prototype<Pololu::Device>(new Device(it->first), it->second));
}

Pololu::Usc::Device::Names::Names() {
  (*this)[typeMaestro6] =
    "Pololu Micro Maestro 6-Channel USB Servo Controller";
  (*this)[typeMaestro6b] =
    "Pololu Micro Maestro 6-Channel USB Servo Controller (Bootloader)";
  (*this)[typeMaestro12] =
    "Pololu Mini Maestro 12-Channel USB Servo Controller";
  (*this)[typeMaestro12b] =
    "Pololu Mini Maestro 12-Channel USB Servo Controller (Bootloader)";
  (*this)[typeMaestro18] =
    "Pololu Mini Maestro 18-Channel USB Servo Controller";
  (*this)[typeMaestro18b] =
    "Pololu Mini Maestro 18-Channel USB Servo Controller (Bootloader)";
  (*this)[typeMaestro24] =
    "Pololu Mini Maestro 24-Channel USB Servo Controller";
  (*this)[typeMaestro24b] =
    "Pololu Mini Maestro 24-Channel USB Servo Controller (Bootloader)";
}

Pololu::Usc::Device::Protocols::Protocols() {
  for (std::map<Type, std::string>::const_iterator
      it = Singleton<Types>::getInstance().begin();
      it != Singleton<Types>::getInstance().end(); ++it)
    (*this)[it->first]["Usb"] = new Usb::Protocol(it->first);
}

Pololu::Usc::Device::Device(Type productId) :
  Pololu::Device(0x1ffb, productId) {
}

Pololu::Usc::Device::Device(const Device& src) :
  Pololu::Device(src) {
}

Pololu::Usc::Device::~Device() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

std::string Pololu::Usc::Device::Types::operator[](Type productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return "Unknown";
}

Pololu::Usc::Device::SuperType Pololu::Usc::Device::SuperTypes::operator[](
    Type productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return superTypeUnknown;
}

unsigned char Pololu::Usc::Device::StackSizes::operator[](Type productId)
    const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return 0;
}

unsigned char Pololu::Usc::Device::CallStackSizes::operator[](Type productId)
    const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return 0;
}

unsigned char Pololu::Usc::Device::NumChannels::operator[](Type productId)
    const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return 0;
}

unsigned short Pololu::Usc::Device::MaxScriptSizes::operator[](Type productId)
    const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return 0;
}

std::string Pololu::Usc::Device::Names::operator[](Type productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return "Pololu Maestro USB Servo Controller (Unknown)";
}

Pololu::Usc::Device::SuperType Pololu::Usc::Device::getSuperType() const {
  return Singleton<SuperTypes>::getInstance()[(Type)productId];
}

size_t Pololu::Usc::Device::getNumChannels() const {
  return Singleton<NumChannels>::getInstance()[(Type)productId];
}

std::string Pololu::Usc::Device::getName() const {
  return Singleton<Names>::getInstance()[(Type)productId];
}

const Pololu::Device::Protocols& Pololu::Usc::Device::getProtocols() const {
  return Singleton<Protocols>::getInstance()[(Type)productId];
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Device& Pololu::Usc::Device::operator=(const Device& src) {
  Pololu::Device::operator=(src);
  return *this;
}

Pololu::Usc::Device* Pololu::Usc::Device::clone() const {
  return new Device(*this);
}

size_t Pololu::Usc::Device::baudRegisterToBps(unsigned short baudRegister) {
  if (baudRegister)
    return (instructionFrequency+(baudRegister+1)/2)/(baudRegister+1);
  else
    return 0;
}

unsigned short Pololu::Usc::Device::bpsToBaudRegister(size_t bps) {
  if (bps)
    return (instructionFrequency-bps/2)/bps;
  else
    return 0;
}

unsigned short Pololu::Usc::Device::expSpeedToSpeed(unsigned char expSpeed) {
  unsigned short mantissa = expSpeed >> 3;
  unsigned short exponent = expSpeed & 7;

  return mantissa*(1 << exponent);
}

unsigned char Pololu::Usc::Device::speedToExpSpeed(unsigned short speed) {
  unsigned short mantissa = speed;
  unsigned char exponent = 0;

  while (true) {
    if (mantissa < 32)
      return exponent+(mantissa << 3);

    if (exponent == 7)
      return 0xFF;

    exponent += 1;
    mantissa >>= 1;
  }
}
