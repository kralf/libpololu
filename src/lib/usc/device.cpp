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

#include "device.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

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

std::string Pololu::Usc::Device::Names::operator[](Type productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return "Pololu Maestro USB Servo Controller (Unknown)";
}

std::string Pololu::Usc::Device::getName() const {
  return Singleton<Names>::getInstance()[(Type)productId];
}

const Pololu::Protocol& Pololu::Usc::Device::getProtocol(const std::string&
    typeName) const {
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
