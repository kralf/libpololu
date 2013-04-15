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

#ifndef POLOLU_DEVICE_H
#define POLOLU_DEVICE_H

/** \file device.h
  * \brief Abstract Pololu device
  */

#include <map>
#include <iostream>

#include "base/object.h"
#include "base/exception.h"
#include "base/pointer.h"
#include "base/interface.h"
#include "base/protocol.h"

namespace Pololu {
  class Device :
    public Object {
  public:
    /** Types and non-static subclasses
      */
    class FirmwareVersion :
      public Object {
    public:
      /** Construct a Pololu device firmware version
        */
      FirmwareVersion(size_t major = 0, size_t minor = 0);
      FirmwareVersion(const FirmwareVersion& src);

      /** Destroy a Pololu device firmware version
        */
      virtual ~FirmwareVersion();

      /** Access the major version of the device firmware
        */
      size_t getMajor() const;
      void setMajor(size_t major);
      /** Access the minor version of the device firmware
        */
      size_t getMinor() const;
      void setMinor(size_t major);

      /** Pololu device firmware version assignments
        */
      FirmwareVersion& operator=(const FirmwareVersion& src);

      /** Write the firmware version to the given stream
        */
      void write(std::ostream& stream) const;
    protected:
      size_t major;
      size_t minor;
    };

    class Protocols :
      public std::map<std::string, Pointer<Protocol> > {
    public:
      /** Construct a Pololu device protocols object
        */
      Protocols();

      /** Access the Pololu device protocol with the specified type
        * name
        */
      const Protocol& operator[](const std::string& typeName) const;
      using std::map<std::string, Pointer<Protocol> >::operator[];

      /** Write the device protocols to the given stream
        */
      void write(std::ostream& stream) const;
    };

    class InterfaceError :
      public Exception {
    public:
      /** Construct a Pololu device interface error
        */
      InterfaceError();
    };

    class ProtocolError :
      public Exception {
    public:
      /** Construct a Pololu device protocol error
        */
      ProtocolError(const std::string& typeName);
    };

    class ConnectionError :
      public Exception {
    public:
      /** Construct a Pololu device connection error
        */
      ConnectionError();
    };

    /** Construct a Pololu device
      */
    Device(const Device& src);

    /** Destroy a Pololu device
      */
    virtual ~Device();

    /** Access the name of the Pololu device
      */
    virtual std::string getName() const = 0;

    /** Access the vendor ID of the Pololu device
      */
    size_t getVendorId() const;
    /** Access the product ID of the Pololu device
      */
    size_t getProductId() const;

    /** Access the interface of the Pololu device
      */
    void setInterface(const Pointer<Interface>& interface);
    const Pointer<Interface>& getInterface() const;

    /** Access the protocols of the Pololu device
      */
    virtual const Protocols& getProtocols() const = 0;
    /** Access the protocol with the specified type name
      */
    const Protocol& getProtocol(const std::string& typeName) const;

    /** Pololu device assignments
      */
    Device& operator=(const Device& src);

    /** Clone the Pololu device
      */
    virtual Device* clone() const = 0;

    /** Connect the Pololu device
      */
    void connect();
    /** Disconnect the Pololu device
      */
    void disconnect();

    /** Send the specified request to the Pololu device
      */
    void send(Request& request);

    /** Pololu device queries
      */
    bool isConnected();

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

std::ostream& operator<<(std::ostream& stream, const
  Pololu::Device& device);
std::ostream& operator<<(std::ostream& stream, const
  Pololu::Device::FirmwareVersion& version);
std::ostream& operator<<(std::ostream& stream, const
  Pololu::Device::Protocols& protocols);

#endif
