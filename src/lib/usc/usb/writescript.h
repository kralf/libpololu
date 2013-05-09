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

#ifndef POLOLU_USC_USB_WRITESCRIPT_H
#define POLOLU_USC_USB_WRITESCRIPT_H

/** \brief USB servo controller write script request (USB protocol)
  */

#include "base/exception.h"

#include "usc/usb/blockrequest.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      class WriteScript :
        public BlockRequest {
      public:
        /** Types and non-static subclasses
          */
        class SizeError :
          public Exception {
        public:
          /** Construct a request size error
            */
          SizeError(unsigned short maxSize);
        };

        /** Construct a Pololu USB servo controller write script
          * request
          */
        WriteScript(unsigned short maxSize, const std::vector<unsigned char>&
          byteCode = std::vector<unsigned char>());
        WriteScript(const WriteScript& src);

        /** Access the request's byte code
          */
        const std::vector<unsigned char>& getByteCode() const;
        void setByteCode(const std::vector<unsigned char>& byteCode);

        WriteScript* clone() const;

        void read(std::istream& stream);
      protected:
        unsigned short maxSize;
      };
    };
  };
};

#endif
