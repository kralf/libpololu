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

#ifndef POLOLU_USB_CONTEXT_H
#define POLOLU_USB_CONTEXT_H

/** \file context.h
  * \brief Pololu USB communication context
  */

#include "base/context.h"
#include "base/prototype.h"
#include "base/singleton.h"

#include "usb/interface.h"

struct libusb_context;

namespace Pololu {
  namespace Usb {
    class Context :
      public Pololu::Context {
    public:
      /** Types and non-static subclasses
        */
      enum DebugLevel {
        debugLevelMinimal = 0,
        debugLevelError = 1,
        debugLevelWarning = 2,
        debugLevelVerbose = 3
      };

      class DebugLevels :
        public std::map<DebugLevel, std::string> {
      public:
        /** Construct a debug levels object
          */
        DebugLevels();
      };

      /** Construct a Pololu USB context
        */
      Context(DebugLevel debugLevel = debugLevelMinimal);
      Context(const Context& src);

      /** Destroy a Pololu USB context
        */
      virtual ~Context();

      /** Access the debug level of the Pololu USB context
        */
      void setDebugLevel(DebugLevel debugLevel);
      DebugLevel getDebugLevel() const;

      /** Access all available USB interfaces within the Pololu USB context
        */
      std::list<Interface> getInterfaces() const;

      Interface* getInterface(const std::string& address) const;

      /** Pololu USB context assignments
        */
      Context& operator=(const Context& src);

      /** Clone the Pololu USB context
        */
      Context* clone() const;

      std::list<Pointer<Device> > discoverDevices() const;
    protected:
      DebugLevel debugLevel;
    private:
      libusb_context* context;

      static Prototype<Pololu::Context> prototype;
    };
  };
};

#endif
