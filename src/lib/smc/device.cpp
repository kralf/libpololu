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

#include "base/singleton.h"

#include "device.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

Pololu::SimpleMotorController::Device::Prototypes
  Pololu::SimpleMotorController::Device::prototypes;

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::SimpleMotorController::Device::Prototypes::Prototypes() {
  for (std::map<size_t, std::string>::const_iterator
      it = Singleton<TypeNames>::getInstance().begin();
      it != Singleton<TypeNames>::getInstance().end(); ++it)
    push_back(Prototype<Pololu::Device>(new Device(it->first), it->second));
}

Pololu::SimpleMotorController::Device::TypeNames::TypeNames() {
  (*this)[0x98] = "simple18v15";
  (*this)[0x97] = "simple18v15b";
  (*this)[0x9A] = "simple24v12";
  (*this)[0x99] = "simple24v12b";
  (*this)[0x9C] = "simple18v25";
  (*this)[0x9B] = "simple18v25b";
  (*this)[0x9E] = "simple24v23";
  (*this)[0x9D] = "simple24v23b";
  (*this)[0xA1] = "simple18v7";
  (*this)[0xA0] = "simple18v7b";
}

Pololu::SimpleMotorController::Device::FullNames::FullNames() {
  (*this)[0x98] = "Pololu Simple High-Power Motor Controller 18v15";
  (*this)[0x97] =
    "Pololu Simple High-Power Motor Controller 18v15 (Bootloader)";
  (*this)[0x9A] = "Pololu Simple High-Power Motor Controller 24v12";
  (*this)[0x99] =
    "Pololu Simple High-Power Motor Controller 24v12 (Bootloader)";
  (*this)[0x9C] = "Pololu Simple High-Power Motor Controller 18v25";
  (*this)[0x9B] =
    "Pololu Simple High-Power Motor Controller 8v25 (Bootloader)";
  (*this)[0x9E] = "Pololu Simple High-Power Motor Controller 24v23";
  (*this)[0x9D] =
    "Pololu Simple High-Power Motor Controller 24v23 (Bootloader)";
  (*this)[0xA1] = "Pololu Simple High-Power Motor Controller 18v7";
  (*this)[0xA0] =
    "Pololu Simple High-Power Motor Controller 18v7 (Bootloader)";
}

Pololu::SimpleMotorController::Device::Device(size_t productId) :
  Pololu::Device(0x1ffb, productId) {
}

Pololu::SimpleMotorController::Device::Device(const Device& src) :
  Pololu::Device(src) {
}

Pololu::SimpleMotorController::Device::~Device() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

std::string Pololu::SimpleMotorController::Device::TypeNames::operator[](
    size_t productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return "Unknown";
}

std::string Pololu::SimpleMotorController::Device::FullNames::operator[](
    size_t productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return "Pololu Simple High-Power Motor Controller (Unknown)";
}

std::string Pololu::SimpleMotorController::Device::getTypeName() const {
  return Singleton<TypeNames>::getInstance()[productId];
}

std::string Pololu::SimpleMotorController::Device::getFullName() const {
  return Singleton<FullNames>::getInstance()[productId];
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::SimpleMotorController::Device&
    Pololu::SimpleMotorController::Device::operator=(const Device& src) {
  Pololu::Device::operator=(src);
  return *this;
}

Pololu::Pointer<Pololu::Device> Pololu::SimpleMotorController::Device::clone()
    const {
  return new Device(*this);
}
