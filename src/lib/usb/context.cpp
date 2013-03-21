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

#include <cstdio>

#include <libusb.h>

#include "base/singleton.h"

#include "context.h"
#include "error.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

Pololu::Prototype<Pololu::Context> Pololu::Usb::Context::prototype(
  new Pololu::Usb::Context(), "Usb");

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usb::Context::DebugLevels::DebugLevels() {
  (*this)[debugLevelMinimal] = "Minimal";
  (*this)[debugLevelError] = "Error";
  (*this)[debugLevelWarning] = "Warning";
  (*this)[debugLevelVerbose] = "Verbose";
}

Pololu::Usb::Context::Context(DebugLevel debugLevel) :
  debugLevel(debugLevel),
  context(0) {
  Error::assert(libusb_init(&context));
  libusb_set_debug(context, this->debugLevel);
}

Pololu::Usb::Context::Context(const Context& src) :
  debugLevel(src.debugLevel),
  context(0) {
  Error::assert(libusb_init(&context));
  libusb_set_debug(context, debugLevel);
}

Pololu::Usb::Context::~Context() {
  libusb_exit(context);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void Pololu::Usb::Context::setDebugLevel(DebugLevel debugLevel) {
  this->debugLevel = debugLevel;
  libusb_set_debug(context, this->debugLevel);
}

Pololu::Usb::Context::DebugLevel Pololu::Usb::Context::getDebugLevel() const {
  return debugLevel;
}

std::list<Pololu::Usb::Interface> Pololu::Usb::Context::getInterfaces()
    const {
  std::list<Interface> interfaces;

  libusb_device** devices;
  size_t numDevices = libusb_get_device_list(context, &devices);
  for (int i = 0; i < numDevices; ++i)
    interfaces.push_back(devices[i]);
  libusb_free_device_list(devices, 1);

  return interfaces;
}

Pololu::Usb::Interface* Pololu::Usb::Context::getInterface(const
    std::string& address) const {
  unsigned char deviceBus, deviceAddress;
  Interface* interface = 0;

  if (sscanf(address.c_str(), "%hhu:%hhu", &deviceBus, &deviceAddress) == 2) {
    libusb_device** devices;
    size_t numDevices = libusb_get_device_list(context, &devices);
    for (int i = 0; i < numDevices; ++i)
      if ((libusb_get_bus_number(devices[i]) == deviceBus) &&
        (libusb_get_device_address(devices[i]) == deviceAddress)) {
      interface = new Interface(devices[i]);
      break;
    }
    libusb_free_device_list(devices, 1);
  }

  if (interface)
    return interface;
  else
    throw AddressError(address);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usb::Context& Pololu::Usb::Context::operator=(const Context& src) {
  setDebugLevel(src.debugLevel);
  return *this;
}

Pololu::Usb::Context* Pololu::Usb::Context::clone() const {
  return new Context(*this);
}

std::list<Pololu::Pointer<Pololu::Device> >
    Pololu::Usb::Context::discoverDevices() const {
  std::list<Pointer<Device> > devices;

  const std::map<std::string, Pointer<Device> >&
    prototypes = Singleton<Factory<Device> >::getInstance().getPrototypes();
  std::list<Interface> interfaces = getInterfaces();
  for (std::list<Interface>::const_iterator it = interfaces.begin();
      it != interfaces.end(); ++it)
    for (std::map<std::string, Pointer<Device> >::const_iterator
        jt = prototypes.begin(); jt != prototypes.end(); ++jt)
      if ((it->getDeviceVendorId() == jt->second->getVendorId()) &&
        (it->getDeviceProductId() == jt->second->getProductId())) {
    devices.push_back(jt->second->clone());
    devices.back()->setInterface(new Interface(*it));
  }

  return devices;
}
