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

#ifndef POLOLU_CONFIG_PARAMETER_H
#define POLOLU_CONFIG_PARAMETER_H

/** \file parameter.h
  * \brief Pololu configuration parameter
  */

#include <iostream>
#include <string>
#include <map>

#include "base/object.h"

namespace Pololu {
  namespace Configuration {
    class Parameter :
      public Pololu::Object {
    public:
      /** Construct a Pololu configuration parameter
        */
      Parameter();
      template <typename T> Parameter(const T& value);
      Parameter(const Parameter& src);

      /** Destroy a Pololu configuration parameter
        */
      virtual ~Parameter();

      /** Access the parameter's value
        */
      const std::string& getValue() const;
      template <typename T> T getValue() const;
      template <typename T, typename U> T getValue(const
        std::map<U, std::string>& values) const;
      void setValue(const std::string& value);
      template <typename T> void setValue(const T& value);
      template <typename T, typename U> void setValue(const
        T& value, const std::map<U, std::string>& values);

      /** Pololu configuration parameter assignments
        */
      Parameter& operator=(const Parameter& src);
      template <typename T> Parameter& operator=(const T& value);

      /** Read the configuration parameter from the given stream
        */
      void read(std::istream& stream);

      /** Write the configuration parameter to the given stream
        */
      void write(std::ostream& stream) const;

      /** Pololu configuration parameter conversions
        */
      template <typename T> operator T() const;
    protected:
      std::string value;
    };
  };
};

std::istream& operator>>(std::istream& stream,
  Pololu::Configuration::Parameter& parameter);
std::ostream& operator<<(std::ostream& stream, const
  Pololu::Configuration::Parameter& parameter);

#include "config/parameter.tpp"

#endif
