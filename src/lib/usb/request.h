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

#ifndef POLOLU_USB_REQUEST_H
#define POLOLU_USB_REQUEST_H

/** \brief Pololu USB request
  */

#include <vector>
#include <map>

#include "base/request.h"

struct libusb_device_handle;

namespace Pololu {
  namespace Usb {
    class Request :
      public Pololu::Request {
    friend class Interface;
    public:
      /** Types and non-static subclasses
        */
      enum Type {
        typeStandard,
        typeClass,
        typeVendor,
        typeReserved
      };

      enum Recipient {
        recipientDevice,
        recipientInterface,
        recipientEndpoint,
        recipientOther
      };

      enum Direction {
        directionIn,
        directionOut
      };

      class TypeFlags :
        public std::map<Type, unsigned char> {
      public:
        /** Construct a USB request type flags object
          */
        TypeFlags();
      };

      class RecipientFlags :
        public std::map<Recipient, unsigned char> {
      public:
        /** Construct a USB request recipient flags object
          */
        RecipientFlags();
      };

      class DirectionFlags :
        public std::map<Direction, unsigned char> {
      public:
        /** Construct a USB request direction flags object
          */
        DirectionFlags();
      };

      /** Construct a Pololu USB request
        */
      Request(Type type = typeStandard, Recipient recipient = recipientDevice,
        Direction direction = directionOut, unsigned char request = 0,
        unsigned short value = 0, unsigned short index = 0, const
        std::vector<unsigned char>& data = std::vector<unsigned char>());
      Request(Type type, unsigned char request, unsigned short value,
        unsigned short index, size_t inputDataSize);
      Request(Type type, unsigned char request, unsigned short value,
        unsigned short index, const std::vector<unsigned char>&
        outputData = std::vector<unsigned char>());
      Request(const Request& src);

      /** Destroy a Pololu USB request
        */
      virtual ~Request();

      /** Access the Pololu USB request's type
        */
      Type getType() const;
      void setType(Type type);
      /** Access the Pololu USB request's recipient
        */
      Recipient getRecipient() const;
      void setRecipient(Recipient recipient);
      /** Access the Pololu USB request's direction
        */
      Direction getDirection() const;
      void setDirection(Direction direction);

      /** Access the Pololu USB request's request type field
        */
      unsigned char getRequestType() const;
      /** Access the Pololu USB request's request field
        */
      unsigned char getRequest() const;
      void setRequest(unsigned char request);
      /** Access the Pololu USB request's value field
        */
      unsigned short getValue() const;
      void setValue(unsigned short value);
      /** Access the Pololu USB request's index field
        */
      unsigned short getIndex() const;
      void setIndex(unsigned short index);

      /** Access the Pololu USB request's data
        */
      const std::vector<unsigned char>& getData() const;
      void setData(const std::vector<unsigned char>& data);

      /** Pololu USB request assignments
        */
      Request& operator=(const Request& src);

      /** Clone the Pololu USB request
        */
      virtual Request* clone() const = 0;
    protected:
      Type type;
      Recipient recipient;
      Direction direction;

      unsigned char requestType;
      unsigned char request;
      unsigned short value;
      unsigned short index;

      std::vector<unsigned char> data;

      /** Pololu USB request operations
        */
      virtual void transfer(libusb_device_handle* handle,
        std::vector<unsigned char>& data, double timeout);

      static void transfer(libusb_device_handle* handle, unsigned char
        requestType, unsigned char request, unsigned short value,
        unsigned short index,  std::vector<unsigned char>& data,
        double timeout);
    };
  };
};

#endif
