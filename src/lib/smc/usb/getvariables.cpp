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

#include "getvariables.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::GetVariables::GetVariables() :
  Pololu::Usb::Request(typeVendor, 0x83, 0, 0, sizeof(Variables)) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Smc::Usb::Variables Pololu::Smc::Usb::GetVariables::getResponse()
    const {
  return reinterpret_cast<const Variables&>(data[0]);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Usb::GetVariables* Pololu::Smc::Usb::GetVariables::clone() const {
  return new GetVariables(*this);
}

void Pololu::Smc::Usb::GetVariables::write(std::ostream& stream) const {
  stream << getResponse();
}
