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
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Device::Device(size_t vendorId, size_t productId) :
  vendorId(vendorId),
  productId(productId) {
}

Pololu::Device::Device(const Device& src) :
  vendorId(src.vendorId),
  productId(src.productId),
  interface(src.interface) {
}

Pololu::Device::~Device() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

size_t Pololu::Device::getVendorId() const {
  return vendorId;
}

size_t Pololu::Device::getProductId() const {
  return productId;
}

void Pololu::Device::setInterface(const Pointer<Interface>& interface) {
  this->interface = interface;
}

const Pololu::Pointer<Pololu::Interface>& Pololu::Device::getInterface()
    const {
  return interface;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Device& Pololu::Device::operator=(const Pololu::Device& src) {
  vendorId = src.vendorId;
  productId = src.productId;

  interface = src.interface;

  return *this;
}

void Pololu::Device::write(std::ostream& stream) const {
  stream << getFullName();
}

std::ostream& operator<<(std::ostream& stream, const Pololu::Device&
    device) {
  device.write(stream);
  return stream;
}
