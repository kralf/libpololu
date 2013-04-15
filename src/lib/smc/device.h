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

#ifndef POLOLU_SMC_DEVICE_H
#define POLOLU_SMC_DEVICE_H

/** \file device.h
  * \brief Pololu simple motor controller (SMC) device
  */

#include <list>
#include <map>

#include "base/device.h"
#include "base/prototype.h"

namespace Pololu {
  namespace Smc {
    class Device :
      public Pololu::Device {
    public:
      /** Types and non-static subclasses
        */
      enum Type {
        typeSimple18v15 = 0x98,
        typeSimple18v15b = 0x97,
        typeSimple24v12 = 0x9A,
        typeSimple24v12b = 0x99,
        typeSimple18v25 = 0x9C,
        typeSimple18v25b = 0x9B,
        typeSimple24v23 = 0x9E,
        typeSimple24v23b = 0x9D,
        typeSimple18v7 = 0xA1,
        typeSimple18v7b = 0xA0
      };

      enum InputChannel {
        inputChannelRc1 = 0,
        inputChannelRc2 = 1,
        inputChannelAnalog1 = 2,
        inputChannelAnalog2 = 3,
      };

      enum MotorLimit {
        motorLimitsForward = 0,
        motorLimitsReverse = 1
      };

      class Types :
        public std::map<Type, std::string> {
      public:
        /** Construct a simple motor controller types object
          */
        Types();

        /** Access the simple motor controller type for the specified
          * product ID
          */
        std::string operator[](Type productId) const;
        using std::map<Type, std::string>::operator[];
      };

      class InputChannels :
        public std::map<InputChannel, std::string> {
      public:
        /** Construct an input channels object
          */
        InputChannels();
      };

      class MotorLimits :
        public std::map<MotorLimit, std::string> {
      public:
        /** Construct a motor limits object
          */
        MotorLimits();
      };

      class Prototypes :
        public std::list<Prototype<Pololu::Device> > {
      public:
        /** Construct a simple motor controller prototypes object
          */
        Prototypes();
      };

      class Names :
        public std::map<Type, std::string> {
      public:
        /** Construct a simple motor controller names object
          */
        Names();

        /** Access the simple motor controller name for the
          * specified product ID
          */
        std::string operator[](Type productId) const;
        using std::map<Type, std::string>::operator[];
      };

      class Protocols :
        public Pololu::Device::Protocols {
      public:
        /** Construct a simple motor controller protocols object
          */
        Protocols();
      };

      /** Construct a Pololu simple motor controller device
        */
      Device(Type productId);
      Device(const Device& src);

      /** Destroy a Pololu simple motor controller device
        */
      virtual ~Device();

      std::string getName() const;
      const Protocols& getProtocols() const;

      /** Pololu simple motor controller device assignments
        */
      Device& operator=(const Device& src);

      /** Clone the simple motor controller device
        */
      Device* clone() const;

      /** Pololu simple motor controller conversions
        */
      static size_t baudRegisterToBps(unsigned short baudRegister);
      static unsigned short bpsToBaudRegister(size_t bps);

      static size_t brakeRegisterToMs(unsigned short brakeRegister);
      static unsigned short msToBrakeRegister(size_t ms);

      static double temperatureRegisterToDeg(unsigned short tempRegister);
      static unsigned short degToTemperatureRegister(double deg);
    protected:
      static const size_t instructionFrequency;
      static const size_t timeBaseMs;
      static const double temperatureBaseDeg;
    private:
      static Prototypes prototypes;
    };
  };
};

#endif
