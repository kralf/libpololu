/***************************************************************************
 *   Copyright (C) 2013 by Ralf Kaestner                                   *
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

/** \brief Pololu USB communication interface
  */

#include <map>

#include "base/interface.h"

#include "usb/request.h"

struct libusb_device;
struct libusb_device_descriptor;
struct libusb_device_handle;

namespace Pololu {
  namespace Usb {
    class Interface :
      public Pololu::Interface {
    friend class Context;
    public:
      /** Types and non-static subclasses
        */
      class DeviceClasses :
        public std::map<unsigned char, std::string> {
      public:
        /** Construct a USB device classes object
          */
        DeviceClasses();

        /** Access the USB device class for the specified class code
          */
        std::string operator[](unsigned char code) const;
        using std::map<unsigned char, std::string>::operator[];
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
      unsigned char getDeviceBus() const;
      /** Access the address of the device attached to the USB interface
        */
      unsigned char getDeviceAddress() const;
      /** Access the vendor ID of the device attached to the USB interface
        */
      unsigned short getDeviceVendorId() const;
      /** Access the product ID of the device attached to the USB interface
        */
      unsigned short getDeviceProductId() const;
      /** Access the class code of the device attached to the USB interface
        */
      unsigned char getDeviceClassCode() const;
      /** Access the specification release number the device attached to
        * the USB interface
        */
      unsigned short getDeviceSpecification() const;
      /** Access the serial number of the device attached to the USB interface
        */
      std::string getDeviceSerialNumber() const;

      std::string getName() const;

      /** Pololu USB interface assignments
        */
      Interface& operator=(const Interface& src);

      /** Pololu USB interface operations
        */
      void open();
      void close();
      void transfer(Request& request);

      Pointer<Device> discoverDevice() const;

      /** Pololu USB interface queries
        */
      bool isOpen() const;
    protected:
      /** Construct a Pololu USB interface
        */
      Interface(libusb_device* device);

      /** Pololu USB interface operations
        */
      void transfer(Pololu::Request& request);
    private:
      libusb_device* device;
      libusb_device_descriptor* descriptor;
      libusb_device_handle* handle;
    };
  };
};

#endif
