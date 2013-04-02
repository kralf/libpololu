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

#include "getstack.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::Mini::GetStack::GetStack() :
  Pololu::Usb::Request(typeVendor, 0x88, 0, 0, 126*sizeof(short)) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Usc::Usb::Mini::Variables::Stack
    Pololu::Usc::Usb::Mini::GetStack::getResponse() const {
  return Variables::Stack(126, reinterpret_cast<const short*>(&data[0]));
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::Mini::GetStack*
    Pololu::Usc::Usb::Mini::GetStack::clone() const {
  return new GetStack(*this);
}

void Pololu::Usc::Usb::Mini::GetStack::write(std::ostream& stream)
    const {
  stream << getResponse();
}
