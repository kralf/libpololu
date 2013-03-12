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
  * \brief Abstract Pololu device
  */

#include <iostream>

#include "base/object.h"
#include "base/pointer.h"
#include "base/interface.h"

namespace Pololu {
  class Device :
    public Object {
  public:
    /** Construct a Pololu device
      */
    Device(const Device& src);

    /** Destroy a Pololu device
      */
    virtual ~Device();

    /** Access the vendor ID of the Pololu device
      */
    size_t getVendorId() const;
    /** Access the product ID of the Pololu device
      */
    size_t getProductId() const;

    /** Access the type name of the Pololu device
      */
    virtual std::string getTypeName() const = 0;
    /** Access the full name of the Pololu device
      */
    virtual std::string getFullName() const = 0;

    /** Access the interface of the Pololu device
      */
    void setInterface(const Pointer<Interface>& interface);
    const Pointer<Interface>& getInterface() const;

    /** Pololu device assignments
      */
    Device& operator=(const Device& src);

    /** Clone the Pololu device
      */
    virtual Pointer<Device> clone() const = 0;

    /** Write the device to the given stream
      */
    void write(std::ostream& stream) const;
  protected:
    size_t vendorId;
    size_t productId;

    Pointer<Interface> interface;

    /** Construct a Pololu device
      */
    Device(size_t vendorId = 0, size_t productId = 0);
  };
};

std::ostream& operator<<(std::ostream& stream, const Pololu::Device&
  device);

#endif
