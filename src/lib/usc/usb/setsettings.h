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

#ifndef POLOLU_USC_USB_SETSETTINGS_H
#define POLOLU_USC_USB_SETSETTINGS_H

/** \brief USB servo controller set settings request (USB protocol)
  */

#include "usb/request.h"

#include "usc/usb/settings.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      class SetSettings :
        public Pololu::Usb::Request {
      public:
        /** Construct a Pololu USB servo controller set settings
          * request
          */
        SetSettings();

        /** Access the request's settings
          */
        virtual const Settings& getSettings() const = 0;
      protected:
        void transfer(libusb_device_handle* handle,
          std::vector<unsigned char>& data, double timeout);

        template <typename T> void transfer(libusb_device_handle* handle,
          unsigned short index, const T& value, double timeout);
      };
    };
  };
};

#include "usc/usb/setsettings.tpp"

#endif
