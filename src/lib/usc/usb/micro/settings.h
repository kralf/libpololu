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

#ifndef POLOLU_USC_USB_MICRO_SETTINGS_H
#define POLOLU_USC_USB_MICRO_SETTINGS_H

/** \file settings.h
  * \brief Pololu USB micro servo controller settings (USB protocol)
  */

#include "usc/usb/settings.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      namespace Micro {
        class Settings :
          public Pololu::Usc::Usb::Settings {
        public:
          /** Construct a Pololu USB micro servo controller settings object
            */
          Settings();

          void read(const Configuration::Section& section);
          void write(Configuration::Section& section) const;

          /** Pololu USB micro servo controller settings conversions
            */
          static unsigned char channelToPort(unsigned char channel);

          unsigned char servosAvailable;
          unsigned char servoPeriod;
        };
      };
    };
  };
};

#endif
