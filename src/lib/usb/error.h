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

#ifndef POLOLU_USB_ERROR_H
#define POLOLU_USB_ERROR_H

/** \brief Pololu USB error
  */

#include <map>

#include "base/exception.h"
#include "base/singleton.h"

namespace Pololu {
  namespace Usb {
    class Error :
      public Exception {
    public:
      /** Types and non-static subclasses
        */
      enum Code {
        success,
        io,
        parameter,
        access,
        device,
        entity,
        busy,
        timeout,
        overflow,
        pipe,
        interrupt,
        memory,
        support,
        other,
        unknown
      };

      class Codes :
        public std::map<int, Code> {
      public:
        /** Construct a Pololu USB error codes object
          */
        Codes();

        /** Access the USB error code for the specified error
          */
        Code operator[](int error) const;
        using std::map<int, Code>::operator[];
      };

      class Descriptions :
        public std::map<int, std::string> {
      public:
        /** Construct a Pololu USB error descriptions object
          */
        Descriptions();

        /** Access the USB error description for the specified error
          */
        std::string operator[](int error) const;
        using std::map<int, std::string>::operator[];
      };

      /** Construct a Pololu USB error
        */
      Error(int error);
      Error(const Error& error);

      /** Pololu USB error assignments
        */
      Error& operator=(const Error& src);

      /** Pololu USB error comparisons
        */
      bool operator==(Code code) const;
      bool operator!=(Code code) const;

      /** Pololu USB error assertion
        */
      static int assert(int error);
    protected:
      Code code;
    };
  };
};

#endif
