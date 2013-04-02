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

#ifndef POLOLU_USC_USB_MINI_VARIABLES_H
#define POLOLU_USC_USB_MINI_VARIABLES_H

/** \file variables.h
  * \brief Pololu USB mini servo controller variables (USB protocol)
  */

#include <map>

#include "usc/usb/variables.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      namespace Mini {
        #pragma pack(push, 1)
        class Variables :
          public Pololu::Usc::Usb::Variables {
        public:
          /** Types and non-static subclasses
            */
          enum PerformanceError {
            performanceErrorNone = 0,
            performanceErrorAdvancedUpdate = (1 << 0),
            performanceErrorBasicUpdate = (1 << 1),
            performanceErrorPeriod = (1 << 2)
          };

          class PerformanceErrors :
            public std::map<PerformanceError, std::string> {
          public:
            /** Construct a performance errors object
              */
            PerformanceErrors();
          };

          /** Construct a Pololu USB mini servo controller variables object
            */
          Variables();

          /** Write the variables to the given stream
            */
          void write(std::ostream& stream) const;

          unsigned char scriptStatus;
          unsigned char performanceErrorOccurred;
        };
        #pragma pack(pop)
      };
    };
  };
};

std::ostream& operator<<(std::ostream& stream, const
  Pololu::Usc::Usb::Mini::Variables& variables);

#endif