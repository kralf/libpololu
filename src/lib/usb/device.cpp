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

#include <libusb.h>

#include "device.h"

#include "utils/utils.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

const PololuDevice::SpeedStrings PololuDevice::speedStrings;

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

PololuDevice::SpeedStrings::SpeedStrings() {
  (*this)[unknown] = "unknown";
  (*this)[low] = "low";
  (*this)[full] = "full";
  (*this)[high] = "high";
  (*this)[super] = "super";
}

PololuDevice::PololuDevice() :
  device(0) {
}

PololuDevice::PololuDevice(const PololuDevice& src) :
  device(src.device) {
  if (device)
    libusb_ref_device(device);
}

PololuDevice::~PololuDevice() {
  if (device)
    libusb_unref_device(device);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

size_t PololuDevice::getBus() const {
  return libusb_get_bus_number(device);
}

size_t PololuDevice::getAddress() const {
  return libusb_get_device_address(device);
}

PololuDevice::Speed PololuDevice::getSpeed() const {
  return unknown;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

PololuDevice& PololuDevice::operator=(const PololuDevice& src) {
  if (device)
    libusb_unref_device(device);

  device = src.device;

  if (device)
    libusb_ref_device(device);

  return *this;
}

void PololuDevice::write(std::ostream& stream) const {
  stream << "(bus " << getBus() << ", address " << getAddress() << ") ";
  stream << "at " << PololuUtils::convert(getSpeed(), speedStrings) <<
    " speed";
}

std::ostream& operator<<(std::ostream& stream, const PololuDevice& device) {
  device.write(stream);
  return stream;
}
