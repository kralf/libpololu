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

#include "parameter.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Configuration::Parameter::Parameter() {
}

Configuration::Parameter::Parameter(const Configuration::Parameter& src) :
  value(src.value) {
}

Configuration::Parameter::~Parameter() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const std::string& Configuration::Parameter::getValue() const {
  return value;
}

void Configuration::Parameter::setValue(const std::string& value) {
  this->value = value;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Configuration::Parameter& Configuration::Parameter::operator=(const
    Configuration::Parameter& src) {
  value = src.value;
  return *this;
}

void Configuration::Parameter::read(std::istream& stream) {
  stream >> value;
}

void Configuration::Parameter::write(std::ostream& stream) const {
  stream << value;
}

std::istream& operator>>(std::istream& stream, Configuration::Parameter&
    parameter) {
  parameter.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Configuration::Parameter&
    parameter) {
  parameter.write(stream);
  return stream;
}
