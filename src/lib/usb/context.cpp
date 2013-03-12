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

Pololu::Prototype<Pololu::Context> Pololu::USB::Context::prototype(
  new Pololu::USB::Context(), "USB");

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::USB::Context::DebugLevels::DebugLevels() {
  (*this)[minimal] = "minimal";
  (*this)[error] = "error";
  (*this)[warning] = "warning";
  (*this)[verbose] = "verbose";
}

Pololu::USB::Context::Context(DebugLevel debugLevel) :
  debugLevel(debugLevel),
  context(0) {
  Pololu::USB::Error::assert(libusb_init(&context));
  libusb_set_debug(context, this->debugLevel);
}

Pololu::USB::Context::Context(const Context& src) :
  debugLevel(src.debugLevel),
  context(0) {
  Pololu::USB::Error::assert(libusb_init(&context));
  libusb_set_debug(context, debugLevel);
}

Pololu::USB::Context::~Context() {
  libusb_exit(context);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void Pololu::USB::Context::setDebugLevel(DebugLevel debugLevel) {
  this->debugLevel = debugLevel;
  libusb_set_debug(context, this->debugLevel);
}

Pololu::USB::Context::DebugLevel Pololu::USB::Context::getDebugLevel() const {
  return debugLevel;
}

std::list<Pololu::USB::Interface> Pololu::USB::Context::getInterfaces()
    const {
  std::list<Interface> interfaces;

  libusb_device** devices;
  size_t numDevices = libusb_get_device_list(context, &devices);
  for (int i = 0; i < numDevices; ++i)
    interfaces.push_back(devices[i]);
  libusb_free_device_list(devices, 1);

  return interfaces;
}

Pololu::Pointer<Pololu::Interface> Pololu::USB::Context::getInterface(const
    std::string& address) const {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::USB::Context& Pololu::USB::Context::operator=(const Context& src) {
  setDebugLevel(src.debugLevel);
  return *this;
}

Pololu::Pointer<Pololu::Context> Pololu::USB::Context::clone() const {
  return new Context(*this);
}

std::list<Pololu::Pointer<Pololu::Device> >
    Pololu::USB::Context::discoverDevices() const {
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
