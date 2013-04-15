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

#include "base/type.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

template <class C>
Pololu::Pointer<C>::NullError::NullError() :
  Exception("Null pointer access") {
}

template <class C>
Pololu::Pointer<C>::TypeError::TypeError(const std::string& typeName) :
  Exception("Invalid instance type: %s", typeName.c_str()) {
}

template <class C>
Pololu::Pointer<C>::Pointer(C* instance) :
  instance(instance) {
  if (this->instance)
    ++this->instance->numReferences;
}

template <class C>
Pololu::Pointer<C>::Pointer(const Pololu::Pointer<C>& src) :
  instance(src.instance) {
  if (instance)
    ++instance->numReferences;
}

template <class C>
Pololu::Pointer<C>::~Pointer() {
  operator=(0);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

template <class C>
Pololu::Pointer<C>& Pololu::Pointer<C>::operator=(C* instance) {
  if (instance != this->instance) {
    if (this->instance) {
      --this->instance->numReferences;

      if (!this->instance->numReferences)
        delete this->instance;
    }

    this->instance = instance;

    if (this->instance)
      ++this->instance->numReferences;
  }

  return *this;
}

template <class C>
Pololu::Pointer<C>& Pololu::Pointer<C>::operator=(const
    Pololu::Pointer<C>& src) {
  return operator=(src.instance);
}

template <class C>
C* Pololu::Pointer<C>::operator->() const {
  if (instance)
    return instance;
  else
    throw NullError();
}

template <class C>
C& Pololu::Pointer<C>::operator*() const {
  if (instance)
    return *instance;
  else
    throw NullError();
}

template <class C>
template <class D> Pololu::Pointer<D> Pololu::Pointer<C>::typeCast() const {
  if (instance) {
    D* instance = dynamic_cast<D*>(this->instance);

    if (instance)
      return Pointer<D>(instance);
    else
      throw TypeError(Type<D>::getName());
  }
  else
    throw NullError();
}

template <class C>
template <class D> bool Pololu::Pointer<C>::operator==(D* instance) const {
  return (this->instance == instance);
}

template <class C>
template <class D> bool Pololu::Pointer<C>::operator==(const Pointer<D>&
    pointer) const {
  return (instance == pointer.instance);
}

template <class C>
template <class D> bool Pololu::Pointer<C>::operator!=(D* instance) const {
  return (this->instance != instance);
}

template <class C>
template <class D> bool Pololu::Pointer<C>::operator!=(const Pointer<D>&
    pointer) const {
  return (instance != pointer.instance);
}

template <class C>
void Pololu::Pointer<C>::free() {
  if (instance) {
    --instance->numReferences;

    delete instance;

    instance = 0;
  }
  else
    throw NullError();
}

template <class C>
bool Pololu::Pointer<C>::isNull() const {
  return !instance;
}

template <class C>
bool Pololu::Pointer<C>::operator!() const {
  return isNull();
}
