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

#include "base/singleton.h"

#include "context.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

Pololu::Prototype<Pololu::Context> Pololu::Serial::Context::prototype(
  new Pololu::Serial::Context(), "Serial");

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Serial::Context::Context() {
}

Pololu::Serial::Context::~Context() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Serial::Interface* Pololu::Serial::Context::getInterface(
    const std::string& address) const {
  return new Interface(address);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Serial::Context* Pololu::Serial::Context::clone() const {
  return new Context(*this);
}

std::list<Pololu::Pointer<Pololu::Device> >
    Pololu::Serial::Context::discoverDevices() const {
  return std::list<Pointer<Device> >();
}
