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

#ifndef POLOLU_USC_USB_MICRO_GETSETTINGS_H
#define POLOLU_USC_USB_MICRO_GETSETTINGS_H

/** \file getsettings.h
  * \brief USB micro servo controller get settings request (USB protocol)
  */

#include "usc/usb/getsettings.h"

#include "usc/usb/micro/settings.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      namespace Micro {
        class GetSettings :
          public Pololu::Usc::Usb::GetSettings {
        public:
          /** Construct a Pololu USB micro servo controller get
            * settings request
            */
          GetSettings();
          GetSettings(const GetSettings& src);

          /** Access the request's response
            */
          Settings& getResponse();
          const Settings& getResponse() const;

          GetSettings* clone() const;
        protected:
          Settings response;

          void transfer(libusb_device_handle* handle,
            std::vector<unsigned char>& data, double timeout);
          using Pololu::Usc::Usb::GetSettings::transfer;
        };
      };
    };
  };
};

#endif
