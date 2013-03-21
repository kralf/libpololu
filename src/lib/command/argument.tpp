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

#include "base/serializable.h"

#include <sstream>

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

template <typename T> Pololu::Command::Argument::Argument(const std::string&
    description, const std::string& format, const T& value) :
  format(format),
  greedy(false),
  description(description) {
  setValue(value);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

template <typename T> T Pololu::Command::Argument::getValue() const {
  std::istringstream stream(value);
  return Serializable<T>().read(stream);
}

template <typename T> void Pololu::Command::Argument::setValue(
    const T& value) {
  std::ostringstream stream;
  Serializable<T>(value).write(stream);

  this->value = stream.str();
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

template <typename T> Pololu::Command::Argument&
    Pololu::Command::Argument::operator=(const T& value) {
  setValue(value);
}
