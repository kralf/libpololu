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

Pololu::USBServoController::Device::Prototypes
  Pololu::USBServoController::Device::prototypes;

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::USBServoController::Device::Prototypes::Prototypes() {
  for (std::map<size_t, std::string>::const_iterator
      it = Singleton<TypeNames>::getInstance().begin();
      it != Singleton<TypeNames>::getInstance().end(); ++it)
    push_back(Prototype<Pololu::Device>(new Device(it->first), it->second));
}

Pololu::USBServoController::Device::TypeNames::TypeNames() {
  (*this)[0x88] = "maestro6";
  (*this)[0x89] = "maestro6b";
  (*this)[0x8a] = "maestro12";
  (*this)[0x8d] = "maestro12b";
  (*this)[0x8b] = "maestro18";
  (*this)[0x8e] = "maestro18b";
  (*this)[0x8c] = "maestro24";
  (*this)[0x8f] = "maestro24b";
}

Pololu::USBServoController::Device::FullNames::FullNames() {
  (*this)[0x88] = "Pololu Micro Maestro 6-Channel USB Servo Controller";
  (*this)[0x89] =
    "Pololu Micro Maestro 6-Channel USB Servo Controller (Bootloader)";
  (*this)[0x8a] = "Pololu Mini Maestro 12-Channel USB Servo Controller";
  (*this)[0x8d] =
    "Pololu Mini Maestro 12-Channel USB Servo Controller (Bootloader)";
  (*this)[0x8b] = "Pololu Mini Maestro 18-Channel USB Servo Controller";
  (*this)[0x8e] =
    "Pololu Mini Maestro 18-Channel USB Servo Controller (Bootloader)";
  (*this)[0x8c] = "Pololu Mini Maestro 24-Channel USB Servo Controller";
  (*this)[0x8f] =
    "Pololu Mini Maestro 24-Channel USB Servo Controller (Bootloader)";
}

Pololu::USBServoController::Device::Device(size_t productId) :
  Pololu::Device(0x1ffb, productId) {
}

Pololu::USBServoController::Device::Device(const Device& src) :
  Pololu::Device(src) {
}

Pololu::USBServoController::Device::~Device() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

std::string Pololu::USBServoController::Device::TypeNames::operator[](
    size_t productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return "Unknown";
}

std::string Pololu::USBServoController::Device::FullNames::operator[](
    size_t productId) const {
  const_iterator it = find(productId);
  if (it != end())
    return it->second;
  else
    return "Pololu Maestro USB Servo Controller (Unknown)";
}

std::string Pololu::USBServoController::Device::getTypeName() const {
  return Singleton<TypeNames>::getInstance()[productId];
}

std::string Pololu::USBServoController::Device::getFullName() const {
  return Singleton<FullNames>::getInstance()[productId];
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::USBServoController::Device&
    Pololu::USBServoController::Device::operator=(const Device& src) {
  Pololu::Device::operator=(src);
  return *this;
}

Pololu::Pointer<Pololu::Device> Pololu::USBServoController::Device::clone()
    const {
  return new Device(*this);
}
