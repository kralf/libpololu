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

#ifndef POLOLU_REQUEST_H
#define POLOLU_REQUEST_H

/** \file request.h
  * \brief Abstract Pololu communication request
  */

#include <iostream>

#include "base/object.h"
#include "base/exception.h"

namespace Pololu {
  class Request :
    public Object {
  public:
    class ParameterRangeError :
      public Exception {
    public:
      /** Construct a Pololu request parameter range error
        */
      template <typename T, typename U, typename V> ParameterRangeError(
        const T& value, const U& minValue, const V& maxValue);

      /** Pololu request parameter range error assertion
        */
      template <typename T, typename U, typename V> static void assert(
        const T& value, const U& minValue, const V& maxValue);
    };

    /** Construct a Pololu request
      */
    Request();

    /** Destroy a Pololu request
      */
    virtual ~Request();

    /** Clone the Pololu request
      */
    virtual Request* clone() const = 0;

    /** Read the request from the given stream
      */
    virtual void read(std::istream& stream);
    /** Write the request to the given stream
      */
    virtual void write(std::ostream& stream) const;
  };
};

std::istream& operator>>(std::istream& stream, Pololu::Request& request);
std::ostream& operator<<(std::ostream& stream, const Pololu::Request& request);

#include "base/request.tpp"

#endif
