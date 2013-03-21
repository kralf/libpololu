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

#ifndef POLOLU_SERIALIZABLE_H
#define POLOLU_SERIALIZABLE_H

/** \file serializable.h
  * \brief Pololu serializable
  */

#include <iostream>
#include <string>
#include <map>

#include "base/object.h"
#include "base/exception.h"

namespace Pololu {
  template <typename T> class Serializable {
  public:
    /** Types and non-static subclasses
      */
    class SerializationError :
      public Exception {
    public:
      /** Construct a serializable serialization error
        */
      SerializationError();
    };

    class DeserializationError :
      public Exception {
    public:
      /** Construct a serializable deserialization error
        */
      DeserializationError();
    };

    /** Traits
      */
    template <typename U, size_t D = 0> struct Traits {
      static void read(std::istream& stream, U& value);
      static void write(std::ostream& stream, const U& value);
    };

    template <size_t D> struct Traits<unsigned char, D> {
      static void read(std::istream& stream, unsigned char& value);
      static void write(std::ostream& stream, const unsigned char& value);
    };

    /** Construct a Pololu serializable
      */
    Serializable(const T& value = T());
    Serializable(const Serializable<T>& src);

    /** Destroy a Pololu serializable
      */
    virtual ~Serializable();

    /** Pololu serializable assignments
      */
    Serializable<T>& operator=(const Serializable<T>& src);
    Serializable<T>& operator=(const T& value);

    /** Read the serializable from the given stream
      */
    T& read(std::istream& stream);
    template <typename U> T& read(std::istream& stream, const
      std::map<U, std::string>& values);
    /** Write the serializable to the given stream
      */
    void write(std::ostream& stream) const;
    template <typename U> void write(std::ostream& stream,
      const std::map<U, std::string>& values) const;

    /** Pololu serializable conversions
      */
    operator T&();
    operator const T&() const;
  protected:
    T value;
  };
};

template <typename T> std::istream& operator>>(std::istream& stream,
  Pololu::Serializable<T>& serializable);
template <typename T> std::ostream& operator<<(std::ostream& stream,
  const Pololu::Serializable<T>& serializable);

#include "base/serializable.tpp"

#endif
