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

#ifndef POLOLU_CONTEXT_H
#define POLOLU_CONTEXT_H

/** \file context.h
  * \brief Pololu USB context
  */

#include <list>

#include "usb/device.h"

struct libusb_context;

class PololuContext {
public:
  /** Types and non-static subclasses
    */
  enum DebugLevel {
    minimal = 0,
    error = 1,
    warning = 2,
    verbose = 3
  };

  class DebugLevelStrings :
    public std::map<DebugLevel, std::string> {
  public:
    /** Construct a debug level string object
      */
    DebugLevelStrings();
  };

  /** Construct a USB context
    */
  PololuContext(DebugLevel debugLevel = minimal);

  /** Destroy a USB context
    */
  virtual ~PololuContext();

  /** Access the debug level of the USB context
    */
  void setDebugLevel(DebugLevel debugLevel);
  DebugLevel getDebugLevel() const;

  /** Access the devices of the USB context
    */
  std::list<PololuDevice> getDevices() const;

  static const DebugLevelStrings debugLevelStrings;
protected:
  libusb_context* context;

  DebugLevel debugLevel;
};

#endif
