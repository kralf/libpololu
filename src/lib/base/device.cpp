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

Pololu::Device::FirmwareVersion::FirmwareVersion(size_t major, size_t
    minor) :
  major(major),
  minor(minor) {
}

Pololu::Device::FirmwareVersion::FirmwareVersion(const FirmwareVersion& src) :
  major(src.major),
  minor(src.minor) {
}

Pololu::Device::FirmwareVersion::~FirmwareVersion() {
}

Pololu::Device::Protocols::Protocols() {
}

Pololu::Device::InterfaceError::InterfaceError() :
  Exception("Invalid or missing interface") {
}

Pololu::Device::ProtocolError::ProtocolError(const std::string& typeName) :
  Exception("Invalid protocol: %s", typeName.c_str()) {
}

Pololu::Device::ConnectionError::ConnectionError() :
  Exception("Device not connected") {
}

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

size_t Pololu::Device::FirmwareVersion::getMajor() const {
  return major;
}

size_t Pololu::Device::FirmwareVersion::getMinor() const {
  return minor;
}

const Pololu::Protocol& Pololu::Device::Protocols::operator[](const
    std::string& typeName) const {
  const_iterator it = find(typeName);
  if (it != end())
    return *(it->second);
  else
    throw ProtocolError(typeName);
}

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

const Pololu::Protocol& Pololu::Device::getProtocol(const std::string&
    typeName) const {
  return getProtocols()[typeName];
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Device::FirmwareVersion& Pololu::Device::FirmwareVersion::operator=(
    const FirmwareVersion& src) {
  major = src.major;
  minor = src.minor;

  return *this;
}

void Pololu::Device::FirmwareVersion::write(std::ostream& stream) const {
  stream << major << "." << minor;
}

void Pololu::Device::Protocols::write(std::ostream& stream) const {
  for (const_iterator it = begin(); it != end(); ++it) {
    if (it != begin())
      stream << std::endl;
    stream << it->first;
  }
}

Pololu::Device& Pololu::Device::operator=(const Pololu::Device& src) {
  vendorId = src.vendorId;
  productId = src.productId;

  interface = src.interface;

  return *this;
}

void Pololu::Device::connect() {
  if (!interface.isNull())
    interface->open();
  else
    throw InterfaceError();
}

void Pololu::Device::disconnect() {
  if (!interface.isNull())
    interface->close();
}

void Pololu::Device::send(Request& request) {
  if (isConnected())
    interface->transfer(request);
  else
    throw ConnectionError();
}

bool Pololu::Device::isConnected() {
  if (!interface.isNull())
    return interface->isOpen();
  else
    return false;
}

void Pololu::Device::write(std::ostream& stream) const {
  stream << getName();
}

std::ostream& operator<<(std::ostream& stream, const Pololu::Device&
    device) {
  device.write(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Device::FirmwareVersion& version) {
  version.write(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Device::Protocols& protocols) {
  protocols.write(stream);
  return stream;
}
