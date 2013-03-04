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

#include <libusb.h>

#include "context.h"

#include "utils/utils.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

const PololuContext::DebugLevelStrings PololuContext::debugLevelStrings;

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

PololuContext::DebugLevelStrings::DebugLevelStrings() {
  (*this)[minimal] = "minimal";
  (*this)[error] = "error";
  (*this)[warning] = "warning";
  (*this)[verbose] = "verbose";
}

PololuContext::PololuContext(DebugLevel debugLevel) :
  context(0),
  debugLevel(debugLevel) {
  PololuUtils::assert("USB initialization failed:", libusb_init(&context));
  libusb_set_debug(context, this->debugLevel);
}

PololuContext::~PololuContext() {
  libusb_exit(context);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void PololuContext::setDebugLevel(DebugLevel debugLevel) {
  this->debugLevel = debugLevel;
  libusb_set_debug(context, this->debugLevel);
}

PololuContext::DebugLevel PololuContext::getDebugLevel() const {
  return debugLevel;
}

std::list<PololuDevice> PololuContext::getDevices() const {
  std::list<PololuDevice> result;

  libusb_device** devices;
  size_t numDevices = libusb_get_device_list(context, &devices);

  for (int i = 0; i < numDevices; ++i) {
    result.push_back(PololuDevice());
    result.back().device = devices[i];
  }

  libusb_free_device_list(devices, 0);
  return result;
}
