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

#ifndef POLOLU_USC_USB_RESTARTSCRIPTATPARAM_H
#define POLOLU_USC_USB_RESTARTSCRIPTATPARAM_H

/** \file restartscriptatparam.h
  * \brief USB servo controller restart script at request (USB protocol)
  * This version of the request takes a parameter for the subroutine.
  */

#include "usb/request.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      class RestartScriptAtParam :
        public Pololu::Usb::Request {
      public:
        /** Construct a Pololu USB servo controller restart script at
          * request
          */
        RestartScriptAtParam(unsigned char subroutine = 0, short
          parameter = 0);

        /** Access the request's subroutine
          */
        unsigned char getSubroutine() const;
        void setSubroutine(unsigned char subroutine);
        /** Access the request's parameter
          */
        short getParameter() const;
        void setParameter(short parameter);

        RestartScriptAtParam* clone() const;

        void read(std::istream& stream);
      };
    };
  };
};

#endif
