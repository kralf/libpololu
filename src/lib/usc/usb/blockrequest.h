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

#ifndef POLOLU_USC_USB_BLOCKREQUEST_H
#define POLOLU_USC_USB_BLOCKREQUEST_H

/** \file blockrequest.h
  * \brief USB servo controller block request (USB protocol)
  */

#include "usb/request.h"

namespace Pololu {
  namespace Usc {
    namespace Usb {
      class BlockRequest :
        public Pololu::Usb::Request {
      public:
        /** Construct a Pololu USB servo controller block request
          */
        BlockRequest(Type type, unsigned char request, unsigned short
          value, unsigned short startIndex, size_t inputDataSize,
          size_t blockSize = 16);
        BlockRequest(Type type, unsigned char request, unsigned short value,
          unsigned short startIndex, const std::vector<unsigned char>&
          outputData = std::vector<unsigned char>(), size_t blockSize = 16);
        BlockRequest(const BlockRequest& src);

        /** Destroy a Pololu USB servo controller block request
          */
        virtual ~BlockRequest();

        /** Access the block request's block size
          */
        size_t getBlockSize() const;
        void setBlockSize(size_t blockSize);

        /** Pololu USB servo controller block request assignments
          */
        BlockRequest& operator=(const BlockRequest& src);
      protected:
        size_t blockSize;

        void transfer(libusb_device_handle* handle,
          std::vector<unsigned char>& data, double timeout);
      };
    };
  };
};

#endif
