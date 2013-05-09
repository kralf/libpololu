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

#ifndef POLOLU_SERIAL_CONTEXT_H
#define POLOLU_SERIAL_CONTEXT_H

/** \brief Pololu Serial (TTL/USB) communication context
  */

#include "base/context.h"
#include "base/prototype.h"
#include "base/singleton.h"

#include "serial/interface.h"

namespace Pololu {
  namespace Serial {
    class Context :
      public Pololu::Context {
    public:
      /** Construct a Pololu serial context
        */
      Context();

      /** Destroy a Pololu serial context
        */
      virtual ~Context();

      Interface* getInterface(const std::string& address) const;

      /** Clone the Pololu serial context
        */
      Context* clone() const;

      std::list<Pointer<Device> > discoverDevices() const;
    private:
      static Prototype<Pololu::Context> prototype;
    };
  };
};

#endif
