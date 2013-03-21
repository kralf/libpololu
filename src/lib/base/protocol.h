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

#ifndef POLOLU_PROTOCOL_H
#define POLOLU_PROTOCOL_H

/** \file protocol.h
  * \brief Abstract Pololu communication protocol
  */

#include "base/object.h"
#include "base/exception.h"
#include "base/pointer.h"

namespace Pololu {
  class Request;

  class Protocol :
    public Object {
  public:
    /** Types and non-static subclasses
      */
    class RequestError :
      public Exception {
    public:
      /** Construct a protocol request error
        */
      RequestError(const std::string& typeName);
    };

    /** Construct a Pololu protocol
      */
    Protocol();

    /** Destroy a Pololu protocol
      */
    virtual ~Protocol();

    /** Access the name of the Pololu protocol
      */
    virtual std::string getName() const = 0;

    /** Clone the Pololu protocol
      */
    virtual Protocol* clone() const = 0;

    /** Create a Pololu request with the specified type name
      */
    virtual Request* createRequest(const std::string& typeName)
      const = 0;

    /** Pololu protocol queries
      */
    virtual bool hasRequest(const std::string& typeName) const = 0;

    /** Write the protocol to the given stream
      */
    virtual void write(std::ostream& stream) const = 0;
  };
};

std::ostream& operator<<(std::ostream& stream, const
  Pololu::Protocol& protocol);

#include "base/request.h"

#endif