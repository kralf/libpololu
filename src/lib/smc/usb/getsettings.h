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

#ifndef POLOLU_SMC_USB_GETSETTINGS_H
#define POLOLU_SMC_USB_GETSETTINGS_H

/** \brief Simple motor controller get settings request (USB protocol)
  */

#include "usb/request.h"

#include "smc/usb/settings.h"

namespace Pololu {
  namespace Smc {
    namespace Usb {
      class GetSettings :
        public Pololu::Usb::Request {
      public:
        /** Construct a Pololu simple motor controller get
          * settings request
          */
        GetSettings();

        /** Access the request's response
          */
        Pololu::Smc::Usb::Settings getResponse() const;

        GetSettings* clone() const;

        void write(std::ostream& stream) const;
      };
    };
  };
};

#endif
