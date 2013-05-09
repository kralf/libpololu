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

#ifndef POLOLU_USC_USB_MINI_GETVARIABLES_H
#define POLOLU_USC_USB_MINI_GETVARIABLES_H

/** \brief USB mini servo controller get variables request (USB protocol)
  */

#include "usb/request.h"

#include "usc/usb/mini/variables.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      namespace Mini {
        class GetVariables :
          public Pololu::Usb::Request {
        public:
          /** Construct a Pololu USB mini servo controller get variables
            * request
            */
          GetVariables();

          /** Access the request's response
            */
          Variables getResponse() const;

          GetVariables* clone() const;

          void write(std::ostream& stream) const;
        };
      };
    };
  };
};

#endif
