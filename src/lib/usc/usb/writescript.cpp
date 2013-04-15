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

#include "base/serializable.h"

#include "writescript.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::WriteScript::SizeError::SizeError(unsigned short maxSize) :
  Exception("Byte code exceeds maximum size: %u", maxSize) {
}

Pololu::Usc::Usb::WriteScript::WriteScript(unsigned short maxSize,
    const std::vector<unsigned char>& byteCode) :
  BlockRequest(typeVendor, 0xA1, 0, 0),
  maxSize(maxSize) {
  setByteCode(byteCode);
}

Pololu::Usc::Usb::WriteScript::WriteScript(const WriteScript& src) :
  BlockRequest(src),
  maxSize(src.maxSize) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const std::vector<unsigned char>&
    Pololu::Usc::Usb::WriteScript::getByteCode() const {
  return data;
}

void Pololu::Usc::Usb::WriteScript::setByteCode(const
    std::vector<unsigned char>& byteCode) {
  if (byteCode.size() <= maxSize)
    data = byteCode;
  else
    throw SizeError(maxSize);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::WriteScript* Pololu::Usc::Usb::WriteScript::clone() const {
  return new WriteScript(*this);
}

void Pololu::Usc::Usb::WriteScript::read(std::istream& stream) {
  Serializable<std::vector<unsigned char> > byteCode;
  setByteCode(byteCode.read(stream));
}
