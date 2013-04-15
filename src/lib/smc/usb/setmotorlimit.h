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

#ifndef POLOLU_SMC_USB_SETMOTORLIMIT_H
#define POLOLU_SMC_USB_SETMOTORLIMIT_H

/** \file setmotorlimit.h
  * \brief Simple motor controller set motor limit request (USB protocol)
  */

#include <map>

#include "usb/request.h"

namespace Pololu {
  namespace Smc {
    namespace Usb {
      class SetMotorLimit :
        public Pololu::Usb::Request {
      public:
        /** Types and non-static subclasses
          */
        enum Limit {
          limitMaxSpeed = 0,
          limitMaxAcceleration = 1,
          limitMaxDeceleration = 2,
          limitBrakeDuration = 3
        };

        enum Mask {
          maskForwardAndReverse = 0,
          maskForwardOnly = 4,
          maskReverseOnly = 8
        };

        enum Response {
          responseSuccess = 0,
          responseForwardConflict = 1,
          responseReverseConflict = 2,
          responseForwardAndReverseConflict = 3
        };

        class Limits :
          public std::map<Limit, std::string> {
        public:
          /** Construct a limits object
            */
          Limits();
        };

        class Masks :
          public std::map<Mask, std::string> {
        public:
          /** Construct a masks object
            */
          Masks();
        };

        class Responses :
          public std::map<Response, std::string> {
        public:
          /** Construct a responses object
            */
          Responses();
        };

        /** Construct a Pololu simple motor controller set motor
          * limit request
          */
        SetMotorLimit(Limit limit = limitMaxSpeed, Mask
          mask = maskForwardAndReverse, unsigned short value = 0);

        /** Access the request's limit
          */
        Limit getLimit() const;
        void setLimit(Limit limit);
        /** Access the request's mask
          */
        Mask getMask() const;
        void setMask(Mask mask);
        /** Access the request's value
          */
        unsigned short getValue() const;
        void setValue(unsigned short value);

        /** Access the request's response
          */
        Response getResponse() const;

        SetMotorLimit* clone() const;

        void read(std::istream& stream);
        void write(std::ostream& stream) const;
      };
    };
  };
};

#endif
