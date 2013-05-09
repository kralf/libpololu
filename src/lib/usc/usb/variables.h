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

#ifndef POLOLU_USC_USB_VARIABLES_H
#define POLOLU_USC_USB_VARIABLES_H

/** \brief Pololu USB servo controller variables (USB protocol)
  */

#include <map>
#include <iostream>

#include "base/exception.h"

#include "usc/device.h"

namespace Pololu {
  namespace Configuration {
    class Section;
  };

  namespace Usc {
    namespace Usb {
      #pragma pack(push, 1)
      class Variables {
      public:
        /** Types and non-static subclasses
          */
        enum Error {
          errorNone = 0,
          errorSerialSign = (1 << 0),
          errorSerialOverrun = (1 << 1),
          errorSerialBufferFull = (1 << 2),
          errorSerialCrc = (1 << 3),
          errorSerialProtocol = (1 << 4),
          errorSerialTimeout = (1 << 5),
          errorScriptStack = (1 << 6),
          errorScriptCallStack = (1 << 7),
          errorScriptProgramCounter = (1 << 8)
        };

        class Errors :
          public std::map<Error, std::string> {
        public:
          /** Construct an errors object
            */
          Errors();
        };

        class Stack {
        public:
          /** Types and non-static subclasses
            */
          class AccessError :
            public Exception {
          public:
            /** Construct a stack variable access error
              */
            AccessError(int i);
          };

          /** Construct a stack object
            */
          Stack(unsigned char size, const short* variables = 0);

          /** Access the stack's size
            */
          unsigned char getSize() const;
          /** Access the stack variables
            */
          short& operator[](int i);
          const short& operator[](int i) const;

          /** Write the stack to the given section
            */
          void write(Configuration::Section& section) const;
          void write(Configuration::Section& section, unsigned char i)
            const;
          /** Write the stack to the given stream
            */
          void write(std::ostream& stream) const;
        protected:
          std::vector<short> variables;
        };

        class CallStack {
        public:
          /** Types and non-static subclasses
            */
          class AccessError :
            public Exception {
          public:
            /** Construct a call stack address access error
              */
            AccessError(int i);
          };

          /** Construct a call stack object
            */
          CallStack(unsigned char size, const unsigned short*
            addresses = 0);

          /** Access the call stack's size
            */
          unsigned char getSize() const;
          /** Access the call stack addresses
            */
          unsigned short& operator[](int i);
          const unsigned short& operator[](int i) const;

          /** Write the call stack to the given section
            */
          void write(Configuration::Section& section) const;
          void write(Configuration::Section& section, unsigned char i)
            const;
          /** Write the call stack to the given stream
            */
          void write(std::ostream& stream) const;
        protected:
          std::vector<unsigned short> addresses;
        };

        class Servo {
        public:
          /** Construct a Pololu USB servo controller servo variables object
            */
          Servo();

          /** Write the servo variables to the given section
            */
          void write(Configuration::Section& section) const;

          unsigned short position;
          unsigned short target;
          unsigned short speed;
          unsigned char acceleration;
        };

        class Servos {
        public:
          /** Types and non-static subclasses
            */
          class AccessError :
            public Exception {
          public:
            /** Construct a servo variables access error
              */
            AccessError(int i);
          };

          /** Construct a servo variables object
            */
          Servos(size_t numServos, const Servo* variables = 0);

          /** Access the number of servos
            */
          size_t getNumServos() const;
          /** Access the variables of the specified servo
            */
          Servo& operator[](int i);
          const Servo& operator[](int i) const;

          /** Write the servo variables to the given section
            */
          void write(Configuration::Section& section) const;
          /** Write the servo variables to the given stream
            */
          void write(std::ostream& stream) const;
        protected:
          std::vector<Servo> variables;
        };

        /** Construct a Pololu USB servo controller variables object
          */
        Variables();

        /** Write the variables to the given section
          */
        void write(Configuration::Section& section) const;

        unsigned char stackPointer;
        unsigned char callStackPointer;
        unsigned short errorOccurred;
        unsigned short programCounter;
      };
      #pragma pack(pop)
    };
  };
};

std::ostream& operator<<(std::ostream& stream, const
  Pololu::Usc::Usb::Variables::Stack& stack);
std::ostream& operator<<(std::ostream& stream, const
  Pololu::Usc::Usb::Variables::CallStack& callStack);
std::ostream& operator<<(std::ostream& stream, const
  Pololu::Usc::Usb::Variables::Servos& servoVariables);

#endif
