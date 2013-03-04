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

#include <sstream>

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

template <typename T> Configuration::Parameter::Parameter(const T& value) {
  setValue(value);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

template <typename T> T Configuration::Parameter::getValue() const {
  std::istringstream stream(this->value);
  T value;

  if (!(stream >> value))
    error("Bad value conversion", this->value);
  else
    return value;
}

template <typename T> void Configuration::Parameter::setValue(const T&
    value) {
  std::ostringstream stream;

  stream << value;
  this->value = stream.str();
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

template <typename T> Configuration::Parameter&
    Configuration::Parameter::operator=(const T& value) {
  setValue(value);
}

template <typename T> Configuration::Parameter::operator T() const {
  return getValue();
}
