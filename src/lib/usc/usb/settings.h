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

#ifndef POLOLU_USC_USB_SETTINGS_H
#define POLOLU_USC_USB_SETTINGS_H

/** \file settings.h
  * \brief Pololu USB servo controller settings (USB protocol)
  */

#include <map>
#include <iostream>

#include "usc/device.h"

namespace Pololu {
  namespace Configuration {
    class Section;
  };

  namespace Usc {
    namespace Usb {
      class Settings {
      public:
        /** Types and non-static subclasses
          */
        enum SerialMode {
          serialModeUsbDualPort = 0,
          serialModeUsbChained = 1,
          serialModeUartDetectBaudRate = 2,
          serialModeUartFixedBaudRate = 3
        };

        class SerialModes :
          public std::map<SerialMode, std::string> {
        public:
          /** Construct a serial modes object
            */
          SerialModes();
        };

       class Channel {
        public:
          /** Types and non-static subclasses
            */
          enum Mode {
            modeServo = 0,
            modeServoMultiplied = 1,
            modeOutput = 2,
            modeInput = 3
          };

          enum HomeMode {
            homeModeOff = 0,
            homeModeIgnore = 1,
            homeModeGoto = 2
          };

          class Modes :
            public std::map<Mode, std::string> {
          public:
            /** Construct a channel modes object
              */
            Modes();
          };

          class HomeModes :
            public std::map<HomeMode, std::string> {
          public:
            /** Construct a channel home modes object
              */
            HomeModes();
          };

          /** Construct a Pololu USB servo controller channel settings
            * object
            */
          Channel();

          std::string name;
          Mode mode;
          HomeMode homeMode;
          unsigned short home;
          unsigned short minimum;
          unsigned short maximum;
          unsigned short neutral;
          unsigned short range;
          unsigned short speed;
          unsigned char acceleration;
        };

        class DocumentError :
          public Exception {
        public:
          /** Construct a settings document error
            */
          DocumentError(const std::string& name);
        };

        class ChannelError :
          public Exception {
        public:
          /** Construct a channel error
            */
          ChannelError(unsigned char channel);
        };

        /** Construct a Pololu USB servo controller settings object
          */
        Settings(unsigned char numChannels);

        /** Read the settings from the given stream
          */
        void read(std::istream& stream);
        /** Write the settings to the given stream
          */
        void write(std::ostream& stream) const;

        /** Read the settings from the given section
          */
        virtual void read(const Configuration::Section& section);
        /** Write the settings to the given section
          */
        virtual void write(Configuration::Section& section) const;

        SerialMode serialMode;
        unsigned short fixedBaudRateRegister;
        bool enableCrc;
        bool neverSuspend;
        unsigned char serialDeviceNumber;
        unsigned char serialMiniSscOffset;
        unsigned short serialTimeout;
        Device::ScriptStatus scriptStatus;
        std::vector<Channel> channels;
      };
    };
  };
};

std::istream& operator>>(std::istream& stream,
  Pololu::Usc::Usb::Settings& settings);
std::ostream& operator<<(std::ostream& stream, const
  Pololu::Usc::Usb::Settings& settings);

#endif
