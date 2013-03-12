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

#ifndef POLOLU_INTERFACE_H
#define POLOLU_INTERFACE_H

/** \file interface.h
  * \brief Abstract Pololu communication interface
  */

#include "base/object.h"
#include "base/exception.h"

namespace Pololu {
  class Device;

  class Interface :
    public Object {
  public:
    /** Types and non-static subclasses
      */
    class ConnectionError :
      public Exception {
    public:
      /** Construct an interface connection error
        */
      ConnectionError(const std::string& address);
    };

    class ReadError :
      public Exception {
    public:
      /** Construct an interface read error
        */
      ReadError(const std::string& address);
    };

    class WriteError :
      public Exception {
    public:
      /** Construct an interface write error
        */
      WriteError(const std::string& address);
    };

    /** Construct a Pololu interface
      */
    Interface(const Interface& src);

    /** Destroy a Pololu interface
      */
    virtual ~Interface();

    /** Access the address of the Pololu interface
      */
    const std::string& getAddress() const;

    /** Access the type name of the Pololu interface
      */
    virtual std::string getTypeName() const = 0;
    /** Access the full name of the Pololu interface
      */
    virtual std::string getFullName() const = 0;

    /** Pololu interface assignments
      */
    Interface& operator=(const Interface& src);

    /** Connect the Pololu interface
      */
    virtual void connect() = 0;

    /** Disconnect the Pololu interface
      */
    virtual void disconnect() = 0;

    /** Pololu interface queries
      */
    virtual bool isConnected() const = 0;

    /** Write the interface to the given stream
      */
    void write(std::ostream& stream) const;
  protected:
    std::string address;

    /** Construct a Pololu interface
      */
    Interface(const std::string& address = "");
  };
};

std::ostream& operator<<(std::ostream& stream, const Pololu::Interface&
  interface);

#endif
