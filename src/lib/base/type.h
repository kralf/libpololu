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

#ifndef POLOLU_TYPE_H
#define POLOLU_TYPE_H

/** \file type.h
  * \brief Templated Pololu type
  */

#include <string>

namespace Pololu {
  template <class C> class Type {
  public:
    /** Access the name of the Pololu type
      */
    static const std::string& getName();
  protected:
    /** Construct a Pololu type
      */
    Type();

    /** Destroy a Pololu type
      */
    virtual ~Type();
  };
};

#include "base/type.tpp"

#endif