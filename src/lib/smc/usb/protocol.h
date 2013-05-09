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

#ifndef POLOLU_SMC_USB_PROTOCOL_H
#define POLOLU_SMC_USB_PROTOCOL_H

/** \brief USB protocol for the Pololu simple motor controller
  */

#include "usb/protocol.h"

namespace Pololu {
  namespace Smc {
    namespace Usb {
      class Protocol :
        public Pololu::Usb::Protocol {
      public:
        /** Construct a Pololu simple motor controller USB protocol
          */
        Protocol();
        Protocol(const Protocol& src);

        /** Destroy a Pololu simple motor controller USB protocol
          */
        virtual ~Protocol();

        /** Pololu simple motor controller USB protocol assignments
          */
        Protocol& operator=(const Protocol& src);

        /** Clone the simple motor controller USB protocol
          */
        Protocol* clone() const;
      };
    };
  };
};

#endif
