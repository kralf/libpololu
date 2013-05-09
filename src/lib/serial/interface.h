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

#ifndef POLOLU_SERIAL_INTERFACE_H
#define POLOLU_SERIAL_INTERFACE_H

/** \brief Pololu serial communication interface
  */

#include <map>

#include "base/interface.h"

#include "serial/request.h"

namespace Pololu {
  namespace Serial {
    class Interface :
      public Pololu::Interface {
    friend class Context;
    public:
      /** Types and non-static subclasses
        */
      enum Parity {
        parityNone = 0,
        parityOdd = 1,
        parityEven = 2
      };

      class BaudRateError :
        public Exception {
      public:
        /** Construct an serial interface baud rate error
          */
        BaudRateError(size_t baudRate);
      };

      class DataBitsError :
        public Exception {
      public:
        /** Construct an serial interface data bits error
          */
        DataBitsError(unsigned char dataBits);
      };

      class StopBitsError :
        public Exception {
      public:
        /** Construct an serial interface stop bits error
          */
        StopBitsError(unsigned char stopBits);
      };

      class OpenError :
        public Exception {
      public:
        /** Construct a serial interface open error
          */
        OpenError(const std::string& address);
      };

      class SetupError :
        public Exception {
      public:
        /** Construct a serial interface setup error
          */
        SetupError(const std::string& address);
      };

      class SendError :
        public Exception {
      public:
        /** Construct a serial interface send error
          */
        SendError(const std::string& address);
      };

      class ReceiveTimeout :
        public Exception {
      public:
        /** Construct a serial interface receive timeout
          */
        ReceiveTimeout(const std::string& address);
      };

      class ReceiveError :
        public Exception {
      public:
        /** Construct a serial interface receive error
          */
        ReceiveError(const std::string& address);
      };

      class BaudRateFlags :
        public std::map<size_t, unsigned int> {
      public:
        /** Construct a baud rate flags object
          */
        BaudRateFlags();

        /** Access the baud rate flag for the specified baud rate
          */
        unsigned int operator[](size_t baudRate) const;
        using std::map<size_t, unsigned int>::operator[];
      };

      class DataBitsFlags :
        public std::map<unsigned char, unsigned int> {
      public:
        /** Construct a data bits flags object
          */
        DataBitsFlags();

        /** Access the data bits flag for the specified number of
          * data bits
          */
        unsigned int operator[](unsigned char dataBits) const;
        using std::map<unsigned char, unsigned int>::operator[];
      };

      class StopBitsFlags :
        public std::map<unsigned char, unsigned int> {
      public:
        /** Construct a stop bits flags object
          */
        StopBitsFlags();

        /** Access the stop bits flag for the specified number of
          * stop bits
          */
        unsigned int operator[](unsigned char stopBits) const;
        using std::map<unsigned char, unsigned int>::operator[];
      };

      class ParityFlags :
        public std::map<Parity, unsigned int> {
      public:
        /** Construct a parity flags object
          */
        ParityFlags();
      };

      /** Construct a Pololu serial interface
        */
      Interface(const std::string& address = "", size_t baudRate = 9600,
        unsigned char dataBits = 8, unsigned char stopBits = 1, Parity
        parity = parityNone);
      Interface(const Interface& src);

      /** Destroy a Pololu serial interface
        */
      virtual ~Interface();

      /** Access the baud rate of the Pololu serial interface
        */
      size_t getBaudRate() const;
      void setBaudRate(size_t baudRate);
      /** Access the number of data bits of the Pololu serial interface
        */
      unsigned char getDataBits() const;
      void setDataBits(unsigned char dataBits);
      /** Access the number of stop bits of the Pololu serial interface
        */
      unsigned char getStopBits() const;
      void setStopBits(unsigned char stopBits);
      /** Access the parity of the Pololu serial interface
        */
      Parity getParity() const;
      void setParity(Parity parity);

      std::string getName() const;

      /** Pololu serial interface assignments
        */
      Interface& operator=(const Interface& src);

      /** Pololu serial interface operations
        */
      void open();
      void close();
      void transfer(Request& request);

      Pointer<Device> discoverDevice() const;

      /** Pololu serial interface queries
        */
      bool isOpen() const;

      /** Send data over the serial interface
        */
      void send(const std::vector<unsigned char>& data);
      /** Receive data over the serial interface
        */
      void receive(std::vector<unsigned char>& data);
    protected:
      size_t baudRate;
      unsigned char dataBits;
      unsigned char stopBits;
      Parity parity;

      /** Pololu serial interface operations
        */
      void setup();
      void transfer(Pololu::Request& request);
    private:
      int handle;
    };
  };
};

#endif
