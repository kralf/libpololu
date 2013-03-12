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

#ifndef POLOLU_USB_INTERFACE_H
#define POLOLU_USB_INTERFACE_H

/** \file interface.h
  * \brief Pololu USB communication interface
  */

#include <map>

#include "base/interface.h"

struct libusb_device;
struct libusb_device_descriptor;
struct libusb_device_handle;

namespace Pololu {
  namespace USB {
    class Interface :
      public Pololu::Interface {
    friend class Context;
    public:
      /** Types and non-static subclasses
        */
      class DeviceClasses :
        public std::map<size_t, std::string> {
      public:
        /** Construct a USB device classes object
          */
        DeviceClasses();

        /** Access the USB device class for the specified class ID
          */
        std::string operator[](size_t id) const;
        using std::map<size_t, std::string>::operator[];
      };

      /** Construct a Pololu USB interface
        */
      Interface(const Interface& src);

      /** Destroy a Pololu USB interface
        */
      virtual ~Interface();

      /** Access the number of the bus a device is attached to the USB
        * interface
        */
      size_t getDeviceBus() const;
      /** Access the address of the device attached to the USB interface
        */
      size_t getDeviceAddress() const;
      /** Access the vendor ID of the device attached to the USB interface
        */
      size_t getDeviceVendorId() const;
      /** Access the product ID of the device attached to the USB interface
        */
      size_t getDeviceProductId() const;
      /** Access the class ID of the device attached to the USB interface
        */
      size_t getDeviceClassId() const;
      /** Access the specification release number the device attached to
        * the USB interface
        */
      size_t getDeviceSpecification() const;

      std::string getTypeName() const;
      std::string getFullName() const;

      /** Pololu USB interface assignments
        */
      Interface& operator=(const Interface& src);

      /** Pololu USB interface operations
        */
      void connect();
      using Pololu::Interface::connect;
      void disconnect();

      /** Pololu USB interface queries
        */
      bool isConnected() const;
    protected:
      /** Construct a Pololu USB interface
        */
      Interface(libusb_device* device);
    private:
      libusb_device* device;
      libusb_device_descriptor* descriptor;
      libusb_device_handle* handle;
    };
  };
};

#endif
