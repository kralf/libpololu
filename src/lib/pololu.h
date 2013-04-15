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

#ifndef POLOLU_H
#define POLOLU_H

/** \file pololu.h
  * \brief Pololu convenience functions
  */

#include <list>

#include "base/context.h"
#include "base/interface.h"
#include "base/device.h"

namespace Pololu {
  /** Create a communication context of the specified type
    */
  Pointer<Context> createContext(const std::string& typeName);

  /** Create a Pololu device of the specified type
    */
  Pointer<Device> createDevice(const std::string& typeName);

  /** Discover all Pololu devices in all available contexts
    */
  std::list<Pointer<Device> > discoverDevices();
};

#endif
