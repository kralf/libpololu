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

#include "base/singleton.h"
#include "base/serializable.h"

#include "subroutine.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Script::Subroutine::Subroutine(unsigned short address,
    ByteCode::Opcode command) :
  address(address),
  command(command) {
}

Pololu::Script::Subroutine::Subroutine(const Subroutine& src) :
  address(src.address),
  command(src.command) {
}

Pololu::Script::Subroutine::~Subroutine() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned short Pololu::Script::Subroutine::getAddress() const {
  return address;
}

void Pololu::Script::Subroutine::setAddress(unsigned short address) {
  this->address = address;
}

Pololu::Script::ByteCode::Opcode Pololu::Script::Subroutine::getCommand()
    const {
  return command;
}

void Pololu::Script::Subroutine::setCommand(ByteCode::Opcode command) {
  this->command = command;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Script::Subroutine& Pololu::Script::Subroutine::operator=(const
    Subroutine& src) {
  address = src.address;
  command = src.command;

  return *this;
}

void Pololu::Script::Subroutine::read(std::istream& stream) {
  char string[256];

  stream.getline(string, sizeof(string), ':');
  std::istringstream sstream(string);
  sstream >> address;
  command = Serializable<ByteCode::Opcode>().read(stream,
    Singleton<ByteCode::Opcodes>::getInstance());
}

void Pololu::Script::Subroutine::write(std::ostream& stream) const {
  stream << address << ':';
  Serializable<ByteCode::Opcode>(command).write(stream,
    Singleton<ByteCode::Opcodes>::getInstance());
}

std::istream& operator>>(std::istream& stream, Pololu::Script::Subroutine&
    subroutine) {
  subroutine.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Script::Subroutine& subroutine) {
  subroutine.write(stream);
  return stream;
}
