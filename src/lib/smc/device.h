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

#ifndef POLOLU_SMC_DEVICE_H
#define POLOLU_SMC_DEVICE_H

/** \file device.h
  * \brief Pololu simple motor controller device
  */

#include <list>
#include <map>

#include "base/device.h"
#include "base/prototype.h"

namespace Pololu {
  namespace SimpleMotorController {
    class Device :
      public Pololu::Device {
    public:
      /** Types and non-static subclasses
        */
      class Prototypes :
        public std::list<Prototype<Pololu::Device> > {
      public:
        /** Construct a simple motor controller prototypes object
          */
        Prototypes();
      };

      class TypeNames :
        public std::map<size_t, std::string> {
      public:
        /** Construct a simple motor controller type names object
          */
        TypeNames();

        /** Access the simple motor controller type name for the
          * specified product ID
          */
        std::string operator[](size_t productId) const;
        using std::map<size_t, std::string>::operator[];
      };

      class FullNames :
        public std::map<size_t, std::string> {
      public:
        /** Construct a simple motor controller full names object
          */
        FullNames();

        /** Access the simple motor controller full names for the
          * specified product ID
          */
        std::string operator[](size_t productId) const;
        using std::map<size_t, std::string>::operator[];
      };

      /** Construct a Pololu simple motor controller device
        */
      Device(size_t productId);
      Device(const Device& src);

      /** Destroy a Pololu simple motor controller device
        */
      virtual ~Device();

      std::string getTypeName() const;
      std::string getFullName() const;

      /** Pololu simple motor controller device assignments
        */
      Device& operator=(const Device& src);

      /** Clone the simple motor controller device
        */
      Pointer<Pololu::Device> clone() const;
    private:
      static Prototypes prototypes;
    };
  };
};

#endif
