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

#ifndef POLOLU_USC_USB_MINI_SETSETTINGS_H
#define POLOLU_USC_USB_MINI_SETSETTINGS_H

/** \file setsettings.h
  * \brief USB mini servo controller set settings request (USB protocol)
  */

#include "usc/usb/setsettings.h"

#include "usc/usb/mini/settings.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      namespace Mini {
        class SetSettings :
          public Pololu::Usc::Usb::SetSettings {
        public:
          /** Construct a Pololu USB mini servo controller set
            * settings request
            */
          SetSettings(unsigned char numChannels);
          SetSettings(const SetSettings& src);

          /** Access the request's settings
            */
          const Settings& getSettings() const;
          void setSettings(const Settings& settings);

          SetSettings* clone() const;

          void read(std::istream& stream);
        protected:
          Settings settings;

          void transfer(libusb_device_handle* handle,
            std::vector<unsigned char>& data, double timeout);
          using Pololu::Usc::Usb::SetSettings::transfer;
        };
      };
    };
  };
};

#endif
