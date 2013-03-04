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

#include <fstream>

#include <libxml++/libxml++.h>

#include "settings.h"

#include "config.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Configuration::Settings::Settings(const std::string& name, const std::string&
    version) :
  Configuration::Section(name),
  version(version) {
}

Configuration::Settings::Settings(const Configuration::Settings& src) :
  Configuration::Section(src),
  version(src.version) {
}

Configuration::Settings::~Settings() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const std::string& Configuration::Settings::getVersion() const {
  return version;
}

void Configuration::Settings::setVersion(const std::string& version) {
  this->version = version;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Configuration::Settings& Configuration::Settings::operator=(const
    Configuration::Settings& src) {
  version = src.version;
  Configuration::Section::operator=(src);

  return *this;
}

void Configuration::Settings::load(const std::string& filename) {
  std::ifstream file(filename.c_str());

  if (!file.is_open())
    PololuUtils::error("Error opening configuration file for reading",
      filename);
  else
    read(file);
}

void Configuration::Settings::save(const std::string& filename) const {
  std::ofstream file(filename.c_str());

  if (!file.is_open())
    PololuUtils::error("Error opening configuration file for writing",
      filename);
  else
    write(file);
}

Configuration::Settings& Configuration::Settings::clear() {
  Configuration::Section::clear();
  version.clear();

  return *this;
}

void Configuration::Settings::toDocument(xmlpp::Document& document) const {
  document.add_comment("Document format: "PROJECT_NAME
    " configuration file (version "PROJECT_VERSION")");
  Configuration::Section::toDocument(document);
}

void Configuration::Settings::fromElement(const xmlpp::Element& element) {
  Configuration::Section::fromElement(element);

  if (hasParameter("version")) {
    version = (*this)["version"].getValue();
    removeParameter("version");
  }
}

void Configuration::Settings::toElement(xmlpp::Element& element) const {
  element.set_attribute("version", version);
  Configuration::Section::toElement(element);
}
