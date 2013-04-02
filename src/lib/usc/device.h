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

#ifndef POLOLU_USC_DEVICE_H
#define POLOLU_USC_DEVICE_H

/** \file device.h
  * \brief Pololu USB servo controller (USC) device
  */

#include <list>
#include <map>

#include "base/device.h"
#include "base/prototype.h"

namespace Pololu {
  namespace Usc {
    class Device :
      public Pololu::Device {
    public:
      /** Types and non-static subclasses
        */
      enum Type {
        typeMaestro6 = 0x89,
        typeMaestro6b = 0x88,
        typeMaestro12 = 0x8a,
        typeMaestro12b = 0x8d,
        typeMaestro18 = 0x8b,
        typeMaestro18b = 0x8e,
        typeMaestro24 = 0x8c,
        typeMaestro24b = 0x8f
      };

      enum SuperType {
        superTypeUnknown,
        superTypeMicro,
        superTypeMini
      };

      enum ScriptStatus {
        scriptStatusRunning = 0,
        scriptStatusStopped = 1
      };

      class Types :
        public std::map<Type, std::string> {
      public:
        /** Construct a USB servo controller types object
          */
        Types();

        /** Access the USB servo controller type for the specified
          * product ID
          */
        std::string operator[](Type productId) const;
        using std::map<Type, std::string>::operator[];
      };

      class SuperTypes :
        public std::map<Type, SuperType> {
      public:
        /** Construct a USB servo controller super types object
          */
        SuperTypes();

        /** Access the USB servo controller super type for the specified
          * product ID
          */
        SuperType operator[](Type productId) const;
        using std::map<Type, SuperType>::operator[];
      };

      class StackSizes :
        public std::map<Type, unsigned char> {
      public:
        /** Construct a USB servo controller stack sizes object
          */
        StackSizes();

        /** Access the stack size for the USB servo controller
          * with the specified product ID
          */
        unsigned char operator[](Type productId) const;
        using std::map<Type, unsigned char>::operator[];
      };

      class CallStackSizes :
        public std::map<Type, unsigned char> {
      public:
        /** Construct a USB servo controller call stack sizes object
          */
        CallStackSizes();

        /** Access the call stack size for the USB servo controller
          * with the specified product ID
          */
        unsigned char operator[](Type productId) const;
        using std::map<Type, unsigned char>::operator[];
      };

      class NumChannels :
        public std::map<Type, unsigned char> {
      public:
        /** Construct a USB servo controller channel numbers object
          */
        NumChannels();

        /** Access the number of channels for the USB servo controller
          * with the specified product ID
          */
        unsigned char operator[](Type productId) const;
        using std::map<Type, unsigned char>::operator[];
      };

      class MaxScriptSizes :
        public std::map<Type, unsigned short> {
      public:
        /** Construct a USB servo controller maximum script sizes object
          */
        MaxScriptSizes();

        /** Access the maximum script size for the USB servo controller
          * with the specified product ID
          */
        unsigned short operator[](Type productId) const;
        using std::map<Type, unsigned short>::operator[];
      };

      class ScriptStatuses :
        public std::map<ScriptStatus, std::string> {
      public:
        /** Construct a USB servo controller script statuses object
          */
        ScriptStatuses();
      };

      class Prototypes :
        public std::list<Prototype<Pololu::Device> > {
      public:
        /** Construct a USB servo controller prototypes object
          */
        Prototypes();
      };

      class Names :
        public std::map<Type, std::string> {
      public:
        /** Construct a USB servo controller names object
          */
        Names();

        /** Access the USB servo controller name for the
          * specified product ID
          */
        std::string operator[](Type productId) const;
        using std::map<Type, std::string>::operator[];
      };

      class Protocols :
        public std::map<Type, Pololu::Device::Protocols> {
      public:
        /** Construct a USB servo controller protocols object
          */
        Protocols();
      };

      /** Construct a Pololu USB servo controller device
        */
      Device(Type productId);
      Device(const Device& src);

      /** Destroy a Pololu USB servo controller device
        */
      virtual ~Device();

      /** Access the super type of the USB servo controller device
        */
      SuperType getSuperType() const;
      /** Access the number of channels of the USB servo controller device
        */
      size_t getNumChannels() const;

      std::string getName() const;
      const Pololu::Device::Protocols& getProtocols() const;

      /** Pololu USB servo controller device assignments
        */
      Device& operator=(const Device& src);

      /** Clone the USB servo controller device
        */
      Device* clone() const;

      /** Pololu simple motor controller conversions
        */
      static size_t baudRegisterToBps(unsigned short baudRegister);
      static unsigned short bpsToBaudRegister(size_t bps);
      static unsigned short expSpeedToSpeed(unsigned char expSpeed);
      static unsigned char speedToExpSpeed(unsigned short speed);
    protected:
      static const size_t instructionFrequency;
    private:
      static Prototypes prototypes;
    };
  };
};

#endif
