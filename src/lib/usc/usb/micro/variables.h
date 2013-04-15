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

#ifndef POLOLU_USC_USB_MICRO_VARIABLES_H
#define POLOLU_USC_USB_MICRO_VARIABLES_H

/** \file variables.h
  * \brief Pololu USB micro servo controller variables (USB protocol)
  */

#include "usc/usb/variables.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      namespace Micro {
        #pragma pack(push, 1)
        class Variables :
          public Pololu::Usc::Usb::Variables {
        public:
          /** Construct a Pololu USB micro servo controller variables object
            */
          Variables();

          /** Write the variables to the given stream
            */
          void write(std::ostream& stream) const;
        private:
          short reserved0[3];
        public:
          short stack[32];
          unsigned short callStack[10];
          unsigned char scriptStatus;
        private:
          unsigned char reserved1;
        public:
          Servo servos[6];
        };
        #pragma pack(pop)
      };
    };
  };
};

std::ostream& operator<<(std::ostream& stream, const
  Pololu::Usc::Usb::Micro::Variables& variables);

#endif
