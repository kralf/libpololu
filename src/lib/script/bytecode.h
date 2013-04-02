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

#ifndef POLOLU_SCRIPT_BYTECODE_H
#define POLOLU_SCRIPT_BYTECODE_H

/** \file bytecode.h
  * \brief Pololu scripting language bytecode
  */

#include <map>
#include <string>

#include "base/object.h"
#include "base/exception.h"

namespace Pololu {
  namespace Script {
    class ByteCode :
      public Object {
    public:
      /** Types and non-static subclasses
        */
      enum Opcode {
        opcodeQuit,
        opcodeLiteral,
        opcodeLiteral8,
        opcodeLiteralN,
        opcodeLiteral8N,
        opcodeReturn,
        opcodeJump,
        opcodeJumpZ,
        opcodeDelay,
        opcodeGetMs,
        opcodeDepth,
        opcodeDrop,
        opcodeDup,
        opcodeOver,
        opcodePick,
        opcodeSwap,
        opcodeRot,
        opcodeRoll,
        opcodeBitwiseNot,
        opcodeBitwiseAnd,
        opcodeBitwiseOr,
        opcodeBitwiseXor,
        opcodeShiftRight,
        opcodeShiftLeft,
        opcodeLogicalNot,
        opcodeLogicalAnd,
        opcodeLogicalOr,
        opcodeNegate,
        opcodePlus,
        opcodeMinus,
        opcodeTimes,
        opcodeDivide,
        opcodeMod,
        opcodePositive,
        opcodeNegative,
        opcodeNonZero,
        opcodeEquals,
        opcodeNotEquals,
        opcodeMin,
        opcodeMax,
        opcodeLessThan,
        opcodeGreaterThan,
        opcodeServo,
        opcodeServo8Bit,
        opcodeSpeed,
        opcodeAccelaration,
        opcodeGetPosition,
        opcodeGetMovingState,
        opcodeLedOn,
        opcodeLedOff,
        opcodePwm,
        opcodePeek,
        opcodePoke,
        opcodeSerialSendByte,
        opcodeCall
      };

      class Opcodes :
        public std::map<Opcode, std::string> {
      public:
        /** Construct a script bytecodes object
          */
        Opcodes();
      };

      /** Construct a Pololu script bytecode object
        */
      ByteCode();

      /** Destroy a Pololu script bytecode object
        */
      virtual ~ByteCode();
    };
  };
};

#endif
