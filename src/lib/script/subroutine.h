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

#ifndef POLOLU_SCRIPT_SUBROUTINE_H
#define POLOLU_SCRIPT_SUBROUTINE_H

/** \file subroutine.h
  * \brief Pololu scripting language subroutine
  */

#include <iostream>

#include "base/object.h"
#include "base/exception.h"

#include "script/bytecode.h"

namespace Pololu {
  namespace Script {
    class Subroutine :
      public Object {
    public:
      /** Construct a Pololu script subroutine object
        */
      Subroutine(unsigned short address = 0, ByteCode::Opcode
        command = ByteCode::opcodeQuit);
      Subroutine(const Subroutine& src);

      /** Destroy a Pololu script subroutine object
        */
      virtual ~Subroutine();

      /** Access the subroutine's address
        */
      unsigned short getAddress() const;
      void setAddress(unsigned short address);
      /** Access the subroutine's command
        */
      ByteCode::Opcode getCommand() const;
      void setCommand(ByteCode::Opcode command);

      /** Pololu script subroutine assignments
        */
      Subroutine& operator=(const Subroutine& src);

      /** Read the subroutine from the given stream
        */
      void read(std::istream& stream);
      /** Write the subroutine to the given stream
        */
      void write(std::ostream& stream) const;
    protected:
      unsigned short address;
      ByteCode::Opcode command;
    };
  };
};

std::istream& operator>>(std::istream& stream,
  Pololu::Script::Subroutine& subroutine);
std::ostream& operator<<(std::ostream& stream, const
  Pololu::Script::Subroutine& subroutine);

#endif
