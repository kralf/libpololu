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

#include <iomanip>
#include <sstream>

#include <libusb.h>

#include "base/singleton.h"

#include "interface.h"
#include "error.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::USB::Interface::DeviceClasses::DeviceClasses() {
  (*this)[LIBUSB_CLASS_PER_INTERFACE] = "specific";
  (*this)[LIBUSB_CLASS_AUDIO] = "audio";
  (*this)[LIBUSB_CLASS_COMM] = "communication";
  (*this)[LIBUSB_CLASS_HID] = "human interface";
  (*this)[LIBUSB_CLASS_PRINTER] = "printer";
  (*this)[LIBUSB_CLASS_MASS_STORAGE] = "storage";
  (*this)[LIBUSB_CLASS_HUB] = "hub";
  (*this)[LIBUSB_CLASS_DATA] = "data";
  (*this)[LIBUSB_CLASS_VENDOR_SPEC] = "vendor";
}

Pololu::USB::Interface::Interface(libusb_device* device) :
  device(device),
  descriptor(0),
  handle(0) {
  if (this->device) {
    libusb_ref_device(this->device);

    descriptor = new libusb_device_descriptor();
    Pololu::USB::Error::assert(
      libusb_get_device_descriptor(this->device, descriptor));

    std::ostringstream stream;
    stream << std::setw(2) << std::setfill('0') << getDeviceBus() << ":" <<
      std::setw(2) << std::setfill('0') << getDeviceAddress();

    address = stream.str();
  }
}

Pololu::USB::Interface::Interface(const Pololu::USB::Interface& src) :
  Pololu::Interface(src),
  descriptor(src.descriptor ?
    new libusb_device_descriptor(*src.descriptor) : 0),
  device(src.device),
  handle(0) {
  if (device)
    libusb_ref_device(device);
}

Pololu::USB::Interface::~Interface() {
  if (handle)
    disconnect();
  if (descriptor)
    delete descriptor;
  if (device)
    libusb_unref_device(device);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

std::string Pololu::USB::Interface::DeviceClasses::operator[](size_t classId)
    const {
  const_iterator it = find(classId);
  if (it != end())
    return it->second;
  else
    return "other";
}

size_t Pololu::USB::Interface::getDeviceBus() const {
  if (device)
    return libusb_get_bus_number(device);
  else
    return 0;
}

size_t Pololu::USB::Interface::getDeviceAddress() const {
  if (device)
    return libusb_get_device_address(device);
  else
    return 0;
}

size_t Pololu::USB::Interface::getDeviceVendorId() const {
  if (descriptor)
    return descriptor->idVendor;
  else
    return 0;
}

size_t Pololu::USB::Interface::getDeviceProductId() const {
  if (descriptor)
    return descriptor->idProduct;
  else
    return 0;
}

size_t Pololu::USB::Interface::getDeviceClassId() const {
  if (descriptor)
    return descriptor->bDeviceClass;
  else
    return 0;
}

size_t Pololu::USB::Interface::getDeviceSpecification() const {
  if (descriptor)
    return descriptor->bcdUSB;
  else
    return 0;
}

std::string Pololu::USB::Interface::getTypeName() const {
  return "usb";
}

std::string Pololu::USB::Interface::getFullName() const {
  return "Universal Serial Bus (USB)";
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::USB::Interface& Pololu::USB::Interface::operator=(const
    Pololu::USB::Interface& src) {
  if (handle)
    disconnect();
  if (device)
    libusb_unref_device(device);

  device = src.device;
  if (src.descriptor) {
    if (!descriptor)
      descriptor = new  libusb_device_descriptor(*src.descriptor);
    else
      *descriptor = *src.descriptor;
  }
  else if (descriptor) {
    delete descriptor;
    descriptor = 0;
  }

  if (device)
    libusb_ref_device(device);

  Pololu::Interface::operator=(src);

  return *this;
}

void Pololu::USB::Interface::connect() {
  if (!handle)
    Pololu::USB::Error::assert(libusb_open(device, &handle));
}

void Pololu::USB::Interface::disconnect() {
  if (handle) {
    libusb_close(handle);
    handle = 0;
  }
}

bool Pololu::USB::Interface::isConnected() const {
  return handle;
}
