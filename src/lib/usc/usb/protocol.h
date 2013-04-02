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

#ifndef POLOLU_USC_USB_PROTOCOL_H
#define POLOLU_USC_USB_PROTOCOL_H

/** \file protocol.h
  * \brief USB protocol for the Pololu USB servo controller
  */

#include <map>

#include "usb/protocol.h"

#include "usc/device.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      class Protocol :
        public Pololu::Usb::Protocol {
      public:
        /** Types and non-static subclasses
          */
        class SubroutinesIndexes :
          public std::map<Device::Type, unsigned short> {
        public:
          /** Construct a subroutines indexes object
            */
          SubroutinesIndexes();
        };

        /** Construct a Pololu USB servo controller USB protocol
          */
        Protocol(Device::Type type);
        Protocol(const Protocol& src);

        /** Destroy a Pololu USB servo controller USB protocol
          */
        virtual ~Protocol();

        /** Pololu USB servo controller USB protocol assignments
          */
        Protocol& operator=(const Protocol& src);

        /** Clone the USB servo controller USB protocol
          */
        Protocol* clone() const;
      };
    };
  };
};

#endif