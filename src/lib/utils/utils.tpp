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
  /** Driver library error assertion
    */
  static void assert(const char* description, int error);

  /** Templated error handling using runtime exceptions
    */
  template <typename T> static void error(const char* message,
      const T& value) {
    std::ostringstream what;
    what << message << ": " << value;
    throw std::runtime_error(what.str());
  };

  /** Templated string to value conversions
    */
  template <typename T> static T convert(const std::string& string) {
    std::istringstream stream(string);
    T value;

    if (!(stream >> value))
      error("Bad value conversion", string);
    else
      return value;
  };

  /** Templated string to vector conversions
    */
  template <typename T> static void convert(const std::string& string,
      std::vector<T>& values) {
    values.clear();

    std::istringstream stream(string);
    std::string value;

    while (!stream.eof()) {
      std::getline(stream, value, ',');
      values.push_back(PololuUtils::convert<T>(value));
    }
  };

  template <typename T> static std::string convert(const std::vector<T>&
      values) {
    std::ostringstream stream;

    for (int i = 0; i < values.size(); ++i) {
      if (i)
        stream << ", ";
      stream << values[i];
    }

    return stream.str();
  };

  /** Templated string to enumeratable conversions
    */
  template <typename T> static T convert(const std::string& string,
      const std::map<T, std::string>& strings) {
    for (typename std::map<T, std::string>::const_iterator it =
        strings.begin(); it != strings.end(); ++it) {
      if (string == it->second)
        return it->first;
    }

    error("Bad value conversion", string);
  };

  /** Templated enumeratable conversions
    */
  template <typename T, typename U> static U convert(const T& t,
      const std::map<T, U>& presets) {
    typename std::map<T, U>::const_iterator it = presets.find(t);
    if (it == presets.end())
      error("Bad preset conversion", t);
    else
      return it->second;
  };

  template <typename T, typename U> static T convert(const U& u,
      const std::map<T, U>& presets) {
    for (typename std::map<T, U>::const_iterator it = presets.begin();
        it != presets.end(); ++it) {
      if (u == it->second)
        return it->first;
    }

    error("Bad preset conversion", u);
  };
};

#endif
