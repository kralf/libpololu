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

#ifndef POLOLU_SMC_USB_VARIABLES_H
#define POLOLU_SMC_USB_VARIABLES_H

/** \file variables.h
  * \brief Pololu simple motor controller variables (USB protocol)
  */

#include <map>
#include <iostream>

#include "smc/device.h"

namespace Pololu {
  namespace Smc {
    namespace Usb {
      #pragma pack(push, 1)
      class Variables {
      public:
        /** Types and non-static subclasses
          */
        enum Error {
          errorNone = 0,
          errorSafeStart = (1 << 0),
          errorChannelInvalid = (1 << 1),
          errorSerial = (1 << 2),
          errorCommandTimeout = (1 << 3),
          errorLimitSwitch = (1 << 4),
          errorVinLow = (1 << 5),
          errorVinHigh = (1 << 6),
          errorTemperatureHigh = (1 << 7),
          errorMotorDriver = (1 << 8),
          errorLineHigh = (1 << 9)
        };

        enum SerialError {
          serialErrorNone = 0,
          serialErrorParity = (1 << 0),
          serialErrorFrame = (1 << 1),
          serialErrorNoise = (1 << 2),
          serialErrorRxOverrun = (1 << 3),
          serialErrorFormat = (1 << 5),
          serialErrorCrc = (1 << 6)
        };

        enum LimitStatus {
          limitStatusNone = 0,
          limitStatusStartedState = (1 << 0),
          limitStatusTemperature = (1 << 1),
          limitStatusMaxSpeed = (1 << 2),
          limitStatusStartingSpeed = (1 << 3),
          limitStatusAcceleration = (1 << 4),
          limitStatusRc1 = (1 << 5),
          limitStatusRc2 = (1 << 6),
          limitStatusAnalog1 = (1 << 7),
          limitStatusAnalog2 = (1 << 8),
          limitStatusUsbKill = (1 << 9)
        };

        class Errors :
          public std::map<Error, std::string> {
        public:
          /** Construct an errors object
            */
          Errors();
        };

        class SerialErrors :
          public std::map<SerialError, std::string> {
        public:
          /** Construct a serial errors object
            */
          SerialErrors();
        };

        class LimitStatuses :
          public std::map<LimitStatus, std::string> {
        public:
          /** Construct a limit statuses object
            */
          LimitStatuses();
        };

        class InputChannel {
        public:
          /** Construct a Pololu simple motor controller input channel
            * variables object
            */
          InputChannel();

          unsigned short unlimitedRawValue;
          unsigned short rawValue;
          short scaledValue;
        private:
          unsigned short reserved0;
        };

        class MotorLimits {
        public:
          /** Construct a Pololu simple motor controller motor limits
            * variables object
            */
          MotorLimits();

          unsigned short maxSpeed;
          unsigned short maxAcceleration;
          unsigned short maxDeceleration;
          unsigned short brakeDuration;
          unsigned short startingSpeed;
        private:
          unsigned short reserved0;
        };

        /** Construct a Pololu simple motor controller variables object
          */
        Variables();

        /** Write the variables to the given stream
          */
        void write(std::ostream& stream) const;

        unsigned short errorStatus;
        unsigned short errorOccurred;
        unsigned short serialErrorOccurred;
        unsigned short limitStatus;
        InputChannel inputChannels[4];
        short targetSpeed;
        short speed;
        unsigned short brakeAmount;
        unsigned short vinMv;
        unsigned short temperature;
      private:
        unsigned short reserved0;
      public:
        unsigned short rcPeriod;
        unsigned short baudRateRegister;
        int timeMs;
        MotorLimits motorLimits[2];
      };
      #pragma pack(pop)
    };
  };
};

std::ostream& operator<<(std::ostream& stream, const
  Pololu::Smc::Usb::Variables& variables);

#endif
