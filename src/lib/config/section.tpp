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

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

template <typename T> bool Pololu::Configuration::Section::query(const
    std::string& location, T& value) const {
  std::string name = location, sublocation;

  int i = location.find("/");
  if (i >= 0) {
    name = location.substr(0, i);
    sublocation = location.substr(i+1);
  }

  if (sublocation.empty()) {
    std::map<std::string, Parameter>::const_iterator
      it = parameters.find(name);

    if (it != parameters.end()) {
      value = it->second;
      return true;
    }
    else
      return false;
  }
  else {
    std::map<std::string, Section>::const_iterator
      it = sections.find(name);
    
    if (it != sections.end())
      return it->second.query(sublocation, value);
    else
      return false;
  }
}

template <typename T, typename U> bool Pololu::Configuration::Section::query(
    const std::string& location, T& value, const std::map<U, std::string>&
    values) const {
  std::string name = location, sublocation;

  int i = location.find("/");
  if (i >= 0) {
    name = location.substr(0, i);
    sublocation = location.substr(i+1);
  }

  if (sublocation.empty()) {
    std::map<std::string, Parameter>::const_iterator
      it = parameters.find(name);

    if (it != parameters.end()) {
      value = it->second.template getValue<T, U>(values);
      return true;
    }
    else
      return false;
  }
  else {
    std::map<std::string, Section>::const_iterator
      it = sections.find(name);

    if (it != sections.end())
      return it->second.query(sublocation, value);
    else
      return false;
  }
}