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

#ifndef POLOLU_OBJECT_H
#define POLOLU_OBJECT_H

/** \file object.h
  * \brief Pololu object
  */

#include "base/pointer.h"
#include "base/exception.h"

namespace Pololu {
  class Object {
  friend class Memory;
  template <class> friend class Pointer;
  public:
    /** Types and non-static subclasses
      */
    class DestructionError :
      public Exception {
    public:
      /** Construct an object destruction error
        */
      DestructionError();
    };

    /** Construct a Pololu object
      */
    Object();

    /** Destroy a Pololu object
      */
    virtual ~Object();

    /** Access the Pololu object's number of references
      */
    size_t getNumReferences() const;

    /** Pololu object queries
      */
    bool inStack() const;
    template <class C> bool isA() const;
  private:
    size_t numReferences;
  };
};

#include "base/object.tpp"

#endif
