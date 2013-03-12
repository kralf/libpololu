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

#ifndef POLOLU_FACTORY_H
#define POLOLU_FACTORY_H

/** \file factory.h
  * \brief Templated Pololu factory
  */

#include <map>

#include "base/pointer.h"
#include "base/exception.h"

namespace Pololu {
  template <class C> class Factory {
  public:
    /** Types and non-static subclasses
      */
    class TypeError :
      public Exception {
    public:
      /** Construct a factory type error
        */
      TypeError(const std::string& typeName);
    };

    /** Construct a Pololu factory
      */
    Factory();

    /** Destroy a Pololu factory
      */
    virtual ~Factory();

    /** Access all registered prototypes
      */
    const std::map<std::string, Pointer<C> >& getPrototypes() const;
    /** Access the prototype of the specified type
      */
    const C& getPrototype(const std::string& typeName) const;

    /** Create an instance of the specified type
      */
    Pointer<C> create(const std::string& typeName) const;

    /** Register a prototype
      */
    void registerPrototype(const std::string& typeName, const
      Pointer<C>& prototype);

    /** Unregister a prototype
      */
    void unregisterPrototype(const std::string& typeName);

    /** Clear the Pololu factory
      */
    void clear();

    /** Pololu factory queries
      */
    bool isRegistered(const std::string& typeName) const;
  protected:
    std::map<std::string, Pointer<C> > prototypes;
  };
};

#include "base/factory.tpp"

#endif
