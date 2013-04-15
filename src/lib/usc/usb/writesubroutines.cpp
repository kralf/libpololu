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
#include "base/serializable.h"

#include "writesubroutines.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::WriteSubroutines::WriteSubroutines(unsigned short
    startIndex, const std::map<std::string, Script::Subroutine>& subroutines) :
  BlockRequest(typeVendor, 0xA1, 0, startIndex, 256) {
  setSubroutines(subroutines);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void Pololu::Usc::Usb::WriteSubroutines::setSubroutines(const
    std::map<std::string, Script::Subroutine>& subroutines) {
  std::fill(data.begin(), data.end(), 0xFF);

  for (std::map<std::string, Script::Subroutine>::const_iterator
      it = subroutines.begin(); it != subroutines.end(); ++it)
    if (it->second.getCommand() != Script::ByteCode::opcodeCall) {
    data[2*(it->second.getCommand()-128)] = it->second.getAddress() % 256;
    data[2*(it->second.getCommand()-128)+1] = it->second.getAddress() >> 8;
  }
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::WriteSubroutines*
    Pololu::Usc::Usb::WriteSubroutines::clone() const {
  return new WriteSubroutines(*this);
}

void Pololu::Usc::Usb::WriteSubroutines::read(std::istream& stream) {
  Serializable<std::map<std::string, Script::Subroutine> > subroutines;
  setSubroutines(subroutines.read(stream));
}
