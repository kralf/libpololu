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

#ifndef POLOLU_SMC_USB_SETSPEED_H
#define POLOLU_SMC_USB_SETSPEED_H

/** \brief Simple motor controller set speed request (USB protocol)
  */

#include <map>

#include "usb/request.h"

namespace Pololu {
  namespace Smc {
    namespace Usb {
      class SetSpeed :
        public Pololu::Usb::Request {
      public:
        /** Types and non-static subclasses
          */
        enum Direction {
          directionForward = 0,
          directionReverse = 1
        };

        class Directions :
          public std::map<Direction, std::string> {
        public:
          /** Construct a directions object
            */
          Directions();
        };

        /** Construct a Pololu simple motor controller set speed
          * request
          */
        SetSpeed(int value = 0);
        SetSpeed(unsigned short value, Direction direction);

        /** Access the request's value
          */
        int getValue() const;
        void setValue(int value);
        void setValue(unsigned short value, Direction direction);
        /** Access the request's direction
          */
        Direction getDirection() const;
        void setDirection(Direction direction);

        SetSpeed* clone() const;

        void read(std::istream& stream);
      };
    };
  };
};

#endif
