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

#include "interface.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Interface::ConnectionError::ConnectionError(const std::string&
    address) :
  Exception("Error connecting to %s", address.c_str()) {
}

Pololu::Interface::ReadError::ReadError(const std::string& address) :
  Exception("Error reading from %s", address.c_str()) {
}

Pololu::Interface::WriteError::WriteError(const std::string& address) :
  Exception("Error writing to %s", address.c_str()) {
}

Pololu::Interface::Interface(const std::string& address) :
  address(address) {
}

Pololu::Interface::Interface(const Interface& src) :
  address(src.address) {
}

Pololu::Interface::~Interface() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const std::string& Pololu::Interface::getAddress() const {
  return address;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Interface& Pololu::Interface::operator=(const Interface& src) {
  if (isConnected())
    disconnect();

  address = src.address;

  if (src.isConnected())
    connect();

  return *this;
}

void Pololu::Interface::write(std::ostream& stream) const {
  stream << getAddress();
}

std::ostream& operator<<(std::ostream& stream, const Pololu::Interface&
    interface) {
  interface.write(stream);
  return stream;
}
