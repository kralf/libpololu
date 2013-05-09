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

#ifndef POLOLU_MEMORY_H
#define POLOLU_MEMORY_H

/** \brief Pololu memory management
  */

#include "exception.h"

namespace Pololu {
  class Object;

  class Memory {
  public:
    /** Types and non-static subclasses
      */
    class AllocationError :
      public Exception {
    public:
      /** Construct a memory allocation error
        */
      AllocationError();
    };

    class DeallocationError :
      public Exception {
    public:
      /** Construct a memory deallocation error
        */
      DeallocationError();
    };

    /** Access the stack bottom
      */
    static void setStackBottom(const void* stackBottom);
    static const void* getStackBottom();
    /** Access the memory frame size
      */
    static size_t getFrameSize();

    /** Allocate memory on the heap
      */
    static void* allocate(size_t size);
    /** Deallocate memory on the heap
      */
    static void deallocate(void* p);

    /** Check if some pointer points into the stack
      */
    static bool inStack(const void* p);

    /** Assert the destruction of an object
      */
    static void assertDestruction(const Object* object);
    /** Garbage-collect an object
      */
    static void garbageCollect(Object* object);
  protected:
    static const void* stackBottom;

    /** Construct a Pololu memory management object
      */
    Memory();
    /** Destroy a Pololu memory management object
      */
    virtual ~Memory();

    /** Compute the memory frame size
      */
    static size_t computeFrameSize(const char* x);
  };
};

#endif
