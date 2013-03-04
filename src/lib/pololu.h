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

#ifndef POLOLU_UTILS_H
#define POLOLU_UTILS_H

/** \file utils.h
  * \brief Pololu utility functions
  */

#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>

class PololuUtils {
public:
  /** Types and non-static subclasses
    */
  class ErrorPresets : public std::map<int, std::string> {
  public:
    /** Constructors
      */
    ErrorPresets();
  };

  /** Driver library error assertion
    */
  static void assert(const char* description, int err);

  /** Templated error handling using runtime exceptions
    */
  template <typename T> static void error(const char* message, const T& value);

  /** Templated string to value conversions
    */
  template <typename T> static T convert(const std::string& string);

  /** Templated string to vector conversions
    */
  template <typename T> static void convert(const std::string& string,
    std::vector<T>& values);
  template <typename T> static std::string convert(const std::vector<T>&
    values);

  /** Templated string to enumeratable conversions
    */
  template <typename T> static T convert(const std::string& string,
    const std::map<T, std::string>& strings);

  /** Templated enumeratable conversions
    */
  template <typename T, typename U> static U convert(const T& t,
    const std::map<T, U>& presets);
  template <typename T, typename U> static T convert(const U& u,
    const std::map<T, U>& presets);
protected:
  static ErrorPresets errors;
};

#include "utils/utils.tpp"

#endif
