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

#include "bytecode.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Script::ByteCode::Opcodes::Opcodes() {
  (*this)[opcodeQuit] = "QUIT";
  (*this)[opcodeLiteral] = "LITERAL";
  (*this)[opcodeLiteral8] = "LITERAL8";
  (*this)[opcodeLiteralN] = "LITERAL_N";
  (*this)[opcodeLiteral8N] = "LITERAL8_N";
  (*this)[opcodeReturn] = "RETURN";
  (*this)[opcodeJump] = "JUMP";
  (*this)[opcodeJumpZ] = "JUMP_Z";
  (*this)[opcodeDelay] = "DELAY";
  (*this)[opcodeGetMs] = "GET_MS";
  (*this)[opcodeDepth] = "DEPTH";
  (*this)[opcodeDrop] = "DROP";
  (*this)[opcodeDup] = "DUP";
  (*this)[opcodeOver] = "OVER";
  (*this)[opcodePick] = "PICK";
  (*this)[opcodeSwap] = "SWAP";
  (*this)[opcodeRot] = "ROT";
  (*this)[opcodeRoll] = "ROLL";
  (*this)[opcodeBitwiseNot] = "BITWISE_NOT";
  (*this)[opcodeBitwiseAnd] = "BITWISE_AND";
  (*this)[opcodeBitwiseOr] = "BITWISE_OR";
  (*this)[opcodeBitwiseXor] = "BITWISE_XOR";
  (*this)[opcodeShiftRight] = "SHIFT_RIGHT";
  (*this)[opcodeShiftLeft] = "SHIFT_LEFT";
  (*this)[opcodeLogicalNot] = "LOGICAL_NOT";
  (*this)[opcodeLogicalAnd] = "LOGICAL_AND";
  (*this)[opcodeLogicalOr] = "LOGICAL_OR";
  (*this)[opcodeNegate] = "NEGATE";
  (*this)[opcodePlus] = "PLUS";
  (*this)[opcodeMinus] = "MINUS";
  (*this)[opcodeTimes] = "TIMES";
  (*this)[opcodeDivide] = "DIVIDE";
  (*this)[opcodeMod] = "MOD";
  (*this)[opcodePositive] = "POSITIVE";
  (*this)[opcodeNegative] = "NEGATIVE";
  (*this)[opcodeNonZero] = "NONZERO";
  (*this)[opcodeEquals] = "EQUALS";
  (*this)[opcodeNotEquals] = "NOT_EQUALS";
  (*this)[opcodeMin] = "MIN";
  (*this)[opcodeMax] = "MAX";
  (*this)[opcodeLessThan] = "LESS_THAN";
  (*this)[opcodeGreaterThan] = "GREATER_THAN";
  (*this)[opcodeServo] = "SERVO";
  (*this)[opcodeServo8Bit] = "SERVO_8BIT";
  (*this)[opcodeSpeed] = "SPEED";
  (*this)[opcodeAccelaration] = "ACCELERATION";
  (*this)[opcodeGetPosition] = "GET_POSITION";
  (*this)[opcodeGetMovingState] = "GET_MOVING_STATE";
  (*this)[opcodeLedOn] = "LED_ON";
  (*this)[opcodeLedOff] = "LED_OFF";
  (*this)[opcodePwm] = "PWM";
  (*this)[opcodePeek] = "PEEK";
  (*this)[opcodePoke] = "POKE";
  (*this)[opcodeSerialSendByte] = "SERIAL_SEND_BYTE";
  (*this)[opcodeCall] = "CALL";
}

Pololu::Script::ByteCode::ByteCode() {
}

Pololu::Script::ByteCode::~ByteCode() {
}
