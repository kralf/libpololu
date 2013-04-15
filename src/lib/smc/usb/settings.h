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

#ifndef POLOLU_SMC_USB_SETTINGS_H
#define POLOLU_SMC_USB_SETTINGS_H

/** \file settings.h
  * \brief Pololu simple motor controller settings (USB protocol)
  */

#include <map>
#include <iostream>

#include "smc/device.h"

namespace Pololu {
  namespace Smc {
    namespace Usb {
      #pragma pack(push, 1)
      class Settings {
      public:
        /** Types and non-static subclasses
          */
        enum CrcMode {
          crcModeDisabled = 0,
          crcModeCommands = 1,
          crcModeCommandsAndResponses = 3
        };

        enum InputMode {
          inputModeSerialUsb = 0,
          inputModeAnalog = 1,
          inputModeRc = 2
        };

        enum PwmMode {
          pwmModeDriveBrake = 0,
          pwmModeDriveCoast = 1
        };

        enum MixingMode {
          mixingModeNone = 0,
          mixingModeLeft = 1,
          mixingModeRight = 2
        };

        enum SerialMode {
          serialModeBinary = 0,
          serialModeAscii = 1
        };

        class CrcModes :
          public std::map<CrcMode, std::string> {
        public:
          /** Construct a CRC modes object
            */
          CrcModes();
        };

        class InputModes :
          public std::map<InputMode, std::string> {
        public:
          /** Construct an input modes object
            */
          InputModes();
        };

        class PwmModes :
          public std::map<PwmMode, std::string> {
        public:
          /** Construct a PWM modes object
            */
          PwmModes();
        };

        class MixingModes :
          public std::map<MixingMode, std::string> {
        public:
          /** Construct a mixing modes object
            */
          MixingModes();
        };

        class SerialModes :
          public std::map<SerialMode, std::string> {
        public:
          /** Construct a serial modes object
            */
          SerialModes();
        };

       class InputChannel {
        public:
          /** Types and non-static subclasses
            */
          enum AlternateUse {
            alternateUseNone = 0,
            alternateUseLimitForward = 1,
            alternateUseLimitReverse = 2,
            alternateUseKillSwitch = 3
          };

          enum PinMode {
            pinModeFloating = 0,
            pinModePullUp = 1,
            pinModePullDown = 2
          };

          class AlternateUses :
            public std::map<AlternateUse, std::string> {
          public:
            /** Construct an alternate uses object
              */
            AlternateUses();
          };

          class PinModes :
            public std::map<PinMode, std::string> {
          public:
            /** Construct a pin modes object
              */
            PinModes();
          };

          /** Construct a Pololu simple motor controller input channel
            * settings object
            */
          InputChannel();

          bool invert;
          unsigned char scalingDegree;
          unsigned char alternateUse;
          unsigned char pinMode;
          unsigned short errorMin;
          unsigned short errorMax;
          unsigned short inputMin;
          unsigned short inputMax;
          unsigned short inputNeutralMin;
          unsigned short inputNeutralMax;
        };

        class MotorLimits {
        public:
          /** Construct a Pololu simple motor controller motor limit
            * settings object
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

        class DocumentError :
          public Exception {
        public:
          /** Construct a settings document error
            */
          DocumentError(const std::string& name);
        };

        /** Construct a Pololu simple motor controller settings object
          */
        Settings();

        /** Read the settings from the given stream
          */
        void read(std::istream& stream);
        /** Write the settings to the given stream
          */
        void write(std::ostream& stream) const;

        bool neverSuspend;
        bool uartResponseDelay;
        bool useFixedBaudRate;
        bool disableSafeStart;
        unsigned short fixedBaudRateRegister;
        unsigned short speedUpdatePeriod;
        unsigned short commandTimeout;
        unsigned char serialDeviceNumber;
        unsigned char crcMode;
        unsigned short overTempMin;
        unsigned short overTempMax;
        unsigned char inputMode;
        unsigned char pwmMode;
        unsigned char pwmPeriodFactor;
        unsigned char mixingMode;
        unsigned short minPulsePeriod;
        unsigned short maxPulsePeriod;
        unsigned short rcTimeout;
        bool ignorePotDisconnect;
        bool tempLimitGradual;
        unsigned char consecGoodPulses;
        bool motorInvert;
        unsigned char speedZeroBrakeAmount;
        bool ignoreErrLineHigh;
        short vinMultiplierOffset;
        unsigned short lowVinShutoffTimeout;
        unsigned short lowVinShutoffMv;
        unsigned short lowVinStartupMv;
        unsigned short highVinShutoffMv;
        unsigned char serialMode;
      private:
        unsigned char reserved0;
      public:
        InputChannel inputChannels[4];
        MotorLimits motorLimits[2];
      };
      #pragma pack(pop)
    };
  };
};

std::istream& operator>>(std::istream& stream,
  Pololu::Smc::Usb::Settings& settings);
std::ostream& operator<<(std::ostream& stream, const
  Pololu::Smc::Usb::Settings& settings);

#endif
