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

#ifndef POLOLU_USC_USB_MINI_SETTINGS_H
#define POLOLU_USC_USB_MINI_SETTINGS_H

/** \file settings.h
  * \brief Pololu USB mini servo controller settings (USB protocol)
  */

#include "usc/usb/settings.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      namespace Mini {
        class Settings :
          public Pololu::Usc::Usb::Settings {
        public:
          /** Construct a Pololu USB mini servo controller settings object
            */
          Settings(unsigned char numChannels);

          void read(const Configuration::Section& section);
          void write(Configuration::Section& section) const;

          unsigned short servoMultiplier;
          unsigned int servoPeriod;
          bool enablePullups;
        };
      };
    };
  };
};

#endif