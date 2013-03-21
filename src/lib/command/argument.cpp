/***************************************************************************
 *   Copyright (C) 2010 by Ralf Kaestner and Luciano Spinello              *
 *   ralf.kaestner@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your argument) any later version.                                   *
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

#include "argument.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Command::Argument::Argument(const std::string& description, const
    std::string& format, const char* value):
  format(format),
  value(value),
  greedy(false),
  description(description) {
}

Pololu::Command::Argument::Argument(const Argument& src) :
  format(src.format),
  value(src.value),
  greedy(src.greedy),
  description(src.description) {
}

Pololu::Command::Argument::~Argument() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const std::string& Pololu::Command::Argument::getFormat() const {
  return format;
}

const std::string& Pololu::Command::Argument::getValue() const {
  return value;
}

void Pololu::Command::Argument::setValue(const std::string& value) {
  this->value = value;
}

bool Pololu::Command::Argument::getGreedy() const {
  return greedy;
}

void Pololu::Command::Argument::setGreedy(bool greedy) {
  this->greedy = greedy;
}

const std::string& Pololu::Command::Argument::getDescription() const {
  return description;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Command::Argument& Pololu::Command::Argument::operator=(const
    Argument& src) {
  format = src.format;
  value = src.value;
  greedy = src.greedy;

  description = src.description;

  return *this;
}
