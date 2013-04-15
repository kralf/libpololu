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

#include <cstdio>

#include "base/singleton.h"

#include "config/document.h"

#include "variables.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::Variables::Errors::Errors() {
  (*this)[errorNone] = "None";
  (*this)[errorSerialSign] = "SerialSign";
  (*this)[errorSerialOverrun] = "SerialOverrun";
  (*this)[errorSerialBufferFull] = "SerialBufferFull";
  (*this)[errorSerialCrc] = "SerialCrc";
  (*this)[errorSerialProtocol] = "SerialProtocol";
  (*this)[errorSerialTimeout] = "SerialTimeout";
  (*this)[errorScriptStack] = "ScriptStack";
  (*this)[errorScriptCallStack] = "ScriptCallStack";
  (*this)[errorScriptProgramCounter] = "ScriptProgramCounter";
}

Pololu::Usc::Usb::Variables::Stack::AccessError::AccessError(int i) :
  Exception("Invalid stack variable: %d", i) {
}

Pololu::Usc::Usb::Variables::Stack::Stack(unsigned char size, const
    short* variables) :
  variables(size) {
  if (variables)
    for (int i = 0; i < size; ++i)
      this->variables[i] = variables[i];
}

Pololu::Usc::Usb::Variables::CallStack::AccessError::AccessError(int i) :
  Exception("Invalid call stack address: %d", i) {
}

Pololu::Usc::Usb::Variables::CallStack::CallStack(unsigned char size,
    const unsigned short* addresses) :
  addresses(size) {
  if (addresses)
    for (int i = 0; i < size; ++i)
      this->addresses[i] = addresses[i];
}

Pololu::Usc::Usb::Variables::Servo::Servo() :
  position(0),
  target(0),
  speed(0),
  acceleration(0) {
}

Pololu::Usc::Usb::Variables::Servos::AccessError::AccessError(int i) :
  Exception("Invalid servo: %d", i) {
}

Pololu::Usc::Usb::Variables::Servos::Servos(size_t numServos, const
    Servo* variables) :
  variables(numServos) {
  if (variables)
    for (int i = 0; i < numServos; ++i)
      this->variables[i] = variables[i];
}

Pololu::Usc::Usb::Variables::Variables() :
  stackPointer(0),
  callStackPointer(0),
  errorOccurred(errorNone),
  programCounter(0) {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char Pololu::Usc::Usb::Variables::Stack::getSize() const {
  return variables.size();
}

short& Pololu::Usc::Usb::Variables::Stack::operator[](int i) {
  if ((i >= 0) || (i < variables.size()))
    return variables[i];
  else
    throw AccessError(i);
}

const short& Pololu::Usc::Usb::Variables::Stack::operator[](int i) const {
  if ((i >= 0) || (i < variables.size()))
    return variables[i];
  else
    throw AccessError(i);
}

unsigned char Pololu::Usc::Usb::Variables::CallStack::getSize() const {
  return addresses.size();
}

unsigned short& Pololu::Usc::Usb::Variables::CallStack::operator[](int i) {
  if ((i >= 0) || (i < addresses.size()))
    return addresses[i];
  else
    throw AccessError(i);
}

const unsigned short& Pololu::Usc::Usb::Variables::CallStack::operator[](
    int i) const {
  if ((i >= 0) || (i < addresses.size()))
    return addresses[i];
  else
    throw AccessError(i);
}

size_t Pololu::Usc::Usb::Variables::Servos::getNumServos() const {
  return variables.size();
}

Pololu::Usc::Usb::Variables::Servo&
    Pololu::Usc::Usb::Variables::Servos::operator[](int i) {
  if ((i >= 0) && (i < variables.size()))
    return variables[i];
  else
    throw AccessError(i);
}

const Pololu::Usc::Usb::Variables::Servo&
    Pololu::Usc::Usb::Variables::Servos::operator[](int i) const {
  if ((i >= 0) && (i < variables.size()))
    return variables[i];
  else
    throw AccessError(i);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Usc::Usb::Variables::Servo::write(Configuration::Section&
    section) const {
  section["Position"] = position;
  section["Target"] = target;
  section["Speed"] = speed;
  section["Acceleration"] = acceleration;
}

void Pololu::Usc::Usb::Variables::Stack::write(Configuration::Section&
    section) const {
  write(section, variables.size());
}

void Pololu::Usc::Usb::Variables::Stack::write(Configuration::Section&
    section, unsigned char i) const {
  char location[256];

  for (unsigned char j = 0; j <= i; ++j) {
    sprintf(location, "Variable%d", j+1);
    section[location] = (*this)[j];
  }
}

void Pololu::Usc::Usb::Variables::Stack::write(std::ostream& stream) const {
  Pololu::Configuration::Document document("UscStack");

  write(document);
  document.write(stream);
}

void Pololu::Usc::Usb::Variables::CallStack::write(Configuration::Section&
    section) const {
  write(section, addresses.size());
}

void Pololu::Usc::Usb::Variables::CallStack::write(Configuration::Section&
    section, unsigned char i) const {
  char location[256];

  for (unsigned char j = 0; j <= i; ++j) {
    sprintf(location, "Address%d", j+1);
    section[location] = (*this)[j];
  }
}

void Pololu::Usc::Usb::Variables::CallStack::write(std::ostream& stream)
    const {
  Pololu::Configuration::Document document("UscCallStack");

  write(document);
  document.write(stream);
}

void Pololu::Usc::Usb::Variables::Servos::write(Configuration::Section&
    section) const {
  char location[256];
  for (int i = 0; i < variables.size(); ++i) {
    sprintf(location, "Servo%d", i+1);
    variables[i].write(section(location));
  }
}

void Pololu::Usc::Usb::Variables::Servos::write(std::ostream& stream) const {
  Pololu::Configuration::Document document("UscServos");

  write(document);
  document.write(stream);
}

void Pololu::Usc::Usb::Variables::write(Configuration::Section& section)
    const {
  section["StackPointer"] = stackPointer;
  section["CallStackPointer"] = callStackPointer;
  for (int i = 0; i <= 8; ++i)
    section["ErrorOccurred/"+Singleton<Errors>::getInstance()[
      (Error)(1 << i)]] = (bool)(errorOccurred & (1 << i));
  section["ProgramCounter"] = programCounter;
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Usc::Usb::Variables::Stack& stack) {
  stack.write(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Usc::Usb::Variables::CallStack& callStack) {
  callStack.write(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Usc::Usb::Variables::Servos& servoVariables) {
  servoVariables.write(stream);
  return stream;
}
