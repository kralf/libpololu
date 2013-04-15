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

#ifndef POLOLU_SMC_USB_GETRESETFLAGS_H
#define POLOLU_SMC_USB_GETRESETFLAGS_H

/** \file getresetflags.h
  * \brief Simple motor controller get reset flags request (USB protocol)
  */

#include <map>

#include "usb/request.h"

namespace Pololu {
  namespace Smc {
    namespace Usb {
      class GetResetFlags :
        public Pololu::Usb::Request {
      public:
        /** Types and non-static subclasses
          */
        enum Response {
          responseResetPin = 0x04,
          responsePower = 0x0C,
          responseSoftware = 0x14,
          responseWatchdog = 0x24
        };

        class Responses :
          public std::map<Response, std::string> {
        public:
          /** Construct a responses object
            */
          Responses();
        };

        /** Construct a Pololu simple motor controller get reset
          * flags request
          */
        GetResetFlags();

        /** Access the request's response
          */
        Response getResponse() const;

        GetResetFlags* clone() const;

        void write(std::ostream& stream) const;
      };
    };
  };
};

#endif
