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

#ifndef POLOLU_DEVICE_H
#define POLOLU_DEVICE_H

/** \file device.h
  * \brief Pololu USB device
  */

#include <map>
#include <string>

struct libusb_device;

class PololuDevice {
friend class PololuContext;
public:
  /** Types and non-static subclasses
    */
  enum Speed {
    unknown,
    low,
    full,
    high,
    super,
  };

  class SpeedStrings :
    public std::map<Speed, std::string> {
  public:
    /** Construct a speed string object
      */
    SpeedStrings();
  };

  /** Construct a USB device
    */
  PololuDevice();
  PololuDevice(const PololuDevice& src);

  /** Destroy a USB device
    */
  virtual ~PololuDevice();

  /** Access the bus number of the device
    */
  size_t getBus() const;
  /** Access the address of the device
    */
  size_t getAddress() const;
  /** Access the speed of the device
    */
  Speed getSpeed() const;

  /** USB device assignments
    */
  PololuDevice& operator=(const PololuDevice& src);

  /** Write the USB device to the given stream
    */
  void write(std::ostream& stream) const;

  static const SpeedStrings speedStrings;
protected:
  libusb_device* device;
};

std::ostream& operator<<(std::ostream& stream, const PololuDevice& device);

#endif
