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

#ifndef POLOLU_POINTER_H
#define POLOLU_POINTER_H

/** \file pointer.h
  * \brief Templated Pololu pointer
  */

#include "base/exception.h"

namespace Pololu {
  template <class C> class Pointer {
  public:
    /** Types and non-static subclasses
      */
    class NullError :
      public Exception {
    public:
      /** Construct a null pointer error
        */
      NullError();
    };

    class TypeError :
      public Exception {
    public:
      /** Construct a pointer type error
        */
      TypeError(const std::string& typeName);
    };

    /** Construct a Pololu pointer
      */
    Pointer(C* instance = 0);
    Pointer(const Pointer<C>& src);

    /** Destroy a Pololu pointer
      */
    virtual ~Pointer();

    /** Pololu pointer assignments
      */
    Pointer<C>& operator=(C* instance);
    Pointer<C>& operator=(const Pointer<C>& src);

    /** Pololu pointer conversions
      */
    C* operator->() const;
    C& operator*() const;
    template <class D> Pointer<D> typeCast() const;

    /** Pololu pointer comparisons
      */
    template <class D> bool operator==(D* instance) const;
    template <class D> bool operator==(const Pointer<D>& pointer) const;
    template <class D> bool operator!=(D* instance) const;
    template <class D> bool operator!=(const Pointer<D>& pointer) const;

    /** Pololu pointer manipulations
      */
    void free();

    /** Pololu pointer queries
      */
    bool isNull() const;
    bool operator!() const;
  protected:
    C* instance;
  };
};

#include "base/pointer.tpp"

#endif
