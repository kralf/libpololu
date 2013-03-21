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

#include <sstream>
#include <cmath>

#include "base/singleton.h"

#include "usb/protocol.h"

#include "device.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

const size_t Pololu::Smc::Device::instructionFrequency = 72000000;
const size_t Pololu::Smc::Device::timeBaseMs = 4;
const double Pololu::Smc::Device::temperatureBaseDeg = 1e-1;

Pololu::Smc::Device::Prototypes Pololu::Smc::Device::prototypes;

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Device::Types::Types() {
  (*this)[typeSimple18v15] = "Simple18v15";
  (*this)[typeSimple18v15b] = "Simple18v15b";
  (*this)[typeSimple24v12] = "Simple24v12";
  (*this)[typeSimple24v12b] = "Simple24v12b";
  (*this)[typeSimple18v25] = "Simple18v25";
  (*this)[typeSimple18v25b] = "Simple18v25b";
  (*this)[typeSimple24v23] = "Simple24v23";
  (*this)[typeSimple24v23b] = "Simple24v23b";
  (*this)[typeSimple18v7] = "Simple18v7";
  (*this)[typeSimple18v7b] = "Simple18v7b";
}

Pololu::Smc::Device::InputChannels::InputChannels() {
  (*this)[inputChannelRc1] = "Rc1";
  (*this)[inputChannelRc2] = "Rc2";
  (*this)[inputChannelAnalog1] = "Analog1";
  (*this)[inputChannelAnalog2] = "Analog2";
}

Pololu::Smc::Device::MotorLimits::MotorLimits() {
  (*this)[motorLimitsForward] = "ForwardLimits";
  (*this)[motorLimitsReverse] = "ReverseLimits";
}

Pololu::Smc::Device::Prototypes::Prototypes() {
  for (std::map<Type, std::string>::const_iterator
      it = Singleton<Types>::getInstance().begin();
      it != Singleton<Types>::getInstance().end(); ++it)
    push_back(Prototype<Pololu::Device>(new Device(it->first), it->second));
}

Pololu::Smc::Device::Names::Names() {
  (*this)[typeSimple18v15] =
    "Pololu Simple High-Power Motor Controller 18v15";
  (*this)[typeSimple18v15b] =
    "Pololu Simple High-Power Motor Controller 18v15 (Bootloader)";
  (*this)[typeSimple24v12] =
    "Pololu Simple High-Power Motor Controller 24v12";
  (*this)[typeSimple24v12b] =
    "Pololu Simple High-Power Motor Controller 24v12 (Bootloader)";
  (*this)[typeSimple18v25] =
    "Pololu Simple High-Power Motor Controller 18v25";
  (*this)[typeSimple18v25b] =
    "Pololu Simple High-Power Motor Controller 8v25 (Bootloader)";
  (*this)[typeSimple24v23] =
    "Pololu Simple High-Power Motor Controller 24v23";
  (*this)[typeSimple24v23b] =
    "Pololu Simple High-Power Motor Controller 24v23 (Bootloader)";
  (*this)[typeSimple18v7] =
    "Pololu Simple High-Power Motor Controller 18v7";
  (*this)[typeSimple18v7b] =
    "Pololu Simple High-Power Motor Controller 18v7 (Bootloader)";
}

Pololu::Smc::Device::Protocols::Protocols() {
  (*this)["Usb"] = new Pololu::Smc::Usb::Protocol();
}

Pololu::Smc::Device::Device(Type productId) :
  Pololu::Device(0x1ffb, productId) {
}

Pololu::Smc::Device::Device(const Device& src) :
  Pololu::Device(src) {
}

Pololu::Smc::Device::~Device() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

std::string Pololu::Smc::Device::Types::operator[](Type productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return "Unknown";
}

std::string Pololu::Smc::Device::Names::operator[](Type productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return "Pololu Simple High-Power Motor Controller (Unknown)";
}

const Pololu::Protocol& Pololu::Smc::Device::Protocols::operator[](const
    std::string& typeName) const {
  const_iterator it = find(typeName);
  if (it != end())
    return *(it->second);
  else
    throw ProtocolError(typeName);
}

std::string Pololu::Smc::Device::getName() const {
  return Singleton<Names>::getInstance()[(Type)productId];
}

const Pololu::Protocol& Pololu::Smc::Device::getProtocol(const std::string&
    typeName) const {
  return *Singleton<Protocols>::getInstance()[typeName];
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Device& Pololu::Smc::Device::operator=(const Device& src) {
  Pololu::Device::operator=(src);
  return *this;
}

Pololu::Smc::Device* Pololu::Smc::Device::clone() const {
  return new Device(*this);
}

size_t Pololu::Smc::Device::baudRegisterToBps(unsigned short baudRegister) {
  if (baudRegister)
    return instructionFrequency/baudRegister;
  else
    return 0;
}

unsigned short Pololu::Smc::Device::bpsToBaudRegister(size_t bps) {
  if (bps)
    return (instructionFrequency+bps/2)/bps;
  else
    return 0;
}

size_t Pololu::Smc::Device::brakeRegisterToMs(unsigned short brakeRegister) {
  return brakeRegister*timeBaseMs;
}

unsigned short Pololu::Smc::Device::msToBrakeRegister(size_t ms) {
  return ceil(ms/timeBaseMs);
}

double Pololu::Smc::Device::temperatureRegisterToDeg(unsigned short
    tempRegister) {
  return tempRegister*temperatureBaseDeg;
}

unsigned short Pololu::Smc::Device::degToTemperatureRegister(double deg) {
  return round(deg/temperatureBaseDeg);
}
