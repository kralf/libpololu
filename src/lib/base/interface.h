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

#ifndef POLOLU_INTERFACE_H
#define POLOLU_INTERFACE_H

/** \file interface.h
  * \brief Abstract Pololu communication interface
  */

#include <vector>

#include "base/object.h"
#include "base/exception.h"
#include "base/pointer.h"
#include "base/request.h"

namespace Pololu {
  class Device;

  class Interface :
    public Object {
  public:
    /** Types and non-static subclasses
      */
    class OperationError :
      public Exception {
    public:
      /** Construct an interface operation error
        */
      OperationError();
    };

    class RequestError :
      public Exception {
    public:
      /** Construct an interface request error
        */
      RequestError();
    };

    /** Construct a Pololu interface
      */
    Interface(const Interface& src);

    /** Destroy a Pololu interface
      */
    virtual ~Interface();

    /** Access the name of the Pololu interface
      */
    virtual std::string getName() const = 0;

    /** Access the address of the Pololu interface
      */
    const std::string& getAddress() const;
    /** Access the timeout of the Pololu interface
      */
    double getTimeout() const;
    void setTimeout(double timeout);

    /** Pololu interface assignments
      */
    Interface& operator=(const Interface& src);

    /** Open the Pololu interface
      */
    virtual void open() = 0;
    /** Close the Pololu interface
      */
    virtual void close() = 0;

    /** Transfer the specified request via the interface
      */
    virtual void transfer(Request& request) = 0;

    /** Pololu interface queries
      */
    virtual bool isOpen() const = 0;

    /** Write the interface to the given stream
      */
    void write(std::ostream& stream) const;

    /** Discover the Pololu device connected by the interface
      */
    virtual Pointer<Device> discoverDevice() const = 0;
  protected:
    std::string address;
    double timeout;

    /** Construct a Pololu interface
      */
    Interface(const std::string& address = "", double timeout = 1e-2);
  };
};

std::ostream& operator<<(std::ostream& stream, const Pololu::Interface&
  interface);

#include "base/device.h"

#endif
