/***************************************************************************
 *   Copyright (C) 2004 by Ralf Kaestner                                   *
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

#include "base/object.h"

#include "memory.h"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

const void* Pololu::Memory::stackBottom = 0;

#include <iostream>

void __attribute__((constructor)) create() {
  char firstStackVariable;
  Pololu::Memory::setStackBottom(&firstStackVariable);
}

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Memory::AllocationError::AllocationError() :
  Exception("Memory allocation error") {
}

Pololu::Memory::DeallocationError::DeallocationError() :
  Exception("Memory deallocation error") {
}

Pololu::Memory::Memory() {
}

Pololu::Memory::~Memory() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void Pololu::Memory::setStackBottom(const void* stackBottom) {
  Pololu::Memory::stackBottom = stackBottom;
}

const void* Pololu::Memory::getStackBottom() {
  return stackBottom;
}

size_t Pololu::Memory::getFrameSize() {
  char x = 0;
  return computeFrameSize(&x);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void* Pololu::Memory::allocate(size_t size) {
  try {
    void* p = ::operator new(size);
  }
  catch (std::exception& exception) {
    throw AllocationError();
  }
}

void Pololu::Memory::deallocate(void* p) {
  try {
    ::operator delete(p);
  }
  catch (std::exception& exception) {
    throw DeallocationError();
  }
}

bool Pololu::Memory::inStack(const void* p) {
  if (stackBottom) {
    char x;
    const void* stackTop = &x;

    if (stackTop > stackBottom)
      return (p > stackBottom) && (p < stackTop);
    else
      return (p > stackTop) && (p < stackBottom);
  }
  else
    return false;
}

void Pololu::Memory::assertDestruction(const Object* object) {
  if (object->numReferences)
    throw Object::DestructionError();
}

void Pololu::Memory::garbageCollect(Object* object) {
  if (!object->numReferences)
    delete object;
}

size_t Pololu::Memory::computeFrameSize(const char* x) {
  char y = 0;
  return x-&y;
}
