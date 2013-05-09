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

#ifndef POLOLU_USB_PROTOCOL_H
#define POLOLU_USB_PROTOCOL_H

/** \brief Pololu USB protocol
  */

#include <map>

#include "base/protocol.h"
#include "base/pointer.h"

#include "usb/request.h"

namespace Pololu {
  namespace Usb {
    class Protocol :
      public Pololu::Protocol {
    public:
      /** Construct a Pololu USB protocol
        */
      Protocol();
      Protocol(const Protocol& src);

      /** Destroy a Pololu USB protocol
        */
      virtual ~Protocol();

      std::string getName() const;

      /** Pololu USB protocol assignments
        */
      Protocol& operator=(const Protocol& src);

      /** Create a Pololu USB request with the specified type name
        */
      Request* createRequest(const std::string& typeName) const;

      /** Pololu USB protocol queries
        */
      bool hasRequest(const std::string& typeName) const;

      /** Write the USB protocol to the given stream
        */
      void write(std::ostream& stream) const;
    protected:
      std::map<std::string, Pointer<Request> > requests;
    };
  };
};

#endif
