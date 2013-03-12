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

#ifndef POLOLU_CONTEXT_H
#define POLOLU_CONTEXT_H

/** \file context.h
  * \brief Abstract Pololu communication context
  */

#include <list>

#include "base/object.h"
#include "base/exception.h"
#include "base/pointer.h"
#include "base/interface.h"
#include "base/device.h"

namespace Pololu {
  class Context :
    public Object {
  public:
    /** Types and non-static subclasses
      */
    class AddressError :
      public Exception {
    public:
      /** Construct a Pololu context address error
        */
      AddressError(const std::string& address);
    };

    /** Construct a Pololu context
      */
    Context();

    /** Destroy a Pololu context
      */
    virtual ~Context();

    /** Access the Pololu interface corresponding to the specified
      * address within the Pololu context
      */
    virtual Pointer<Interface> getInterface(const std::string&
      address) const = 0;

    /** Clone the Pololu context
      */
    virtual Pointer<Context> clone() const = 0;

    /** Discover all Pololu devices in the context
      */
    virtual std::list<Pointer<Device> > discoverDevices() const = 0;
  };
};

#endif
