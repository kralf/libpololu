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

#ifndef POLOLU_SMC_USB_SETBRAKE_H
#define POLOLU_SMC_USB_SETBRAKE_H

/** \file setbrake.h
  * \brief Simple motor controller set brake request (USB protocol)
  */

#include "usb/request.h"

namespace Pololu {
  namespace Smc {
    namespace Usb {
      class SetBrake :
        public Pololu::Usb::Request {
      public:
        /** Construct a Pololu simple motor controller set brake
          * request
          */
        SetBrake(unsigned short value = 0);

        /** Access the request's value
          */
        unsigned short getValue() const;
        void setValue(unsigned short value);

        SetBrake* clone() const;

        void read(std::istream& stream);
      };
    };
  };
};

#endif
