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

#include "document.h"

#include "config.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Configuration::Document::FileError::FileError(const std::string&
    filename) :
  Exception("Configuration file error: %s", filename.c_str()) {
}

Pololu::Configuration::Document::Document(const std::string& name, const
    std::string& version) :
  Section(name),
  version(version) {
}

Pololu::Configuration::Document::Document(const Document& src) :
  Section(src),
  version(src.version) {
}

Pololu::Configuration::Document::~Document() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const std::string& Pololu::Configuration::Document::getVersion() const {
  return version;
}

void Pololu::Configuration::Document::setVersion(const std::string& version) {
  this->version = version;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Configuration::Document& Pololu::Configuration::Document::operator=(
    const Document& src) {
  version = src.version;
  Section::operator=(src);

  return *this;
}

void Pololu::Configuration::Document::load(const std::string& filename) {
  std::ifstream file(filename.c_str());

  if (file.is_open())
    read(file);
  else
    throw FileError(filename);
}

void Pololu::Configuration::Document::save(const std::string& filename)
    const {
  std::ofstream file(filename.c_str());

  if (file.is_open())
    write(file);
  else
    throw FileError(filename);
}

Pololu::Configuration::Document& Pololu::Configuration::Document::clear() {
  Pololu::Configuration::Section::clear();
  version.clear();

  return *this;
}

void Pololu::Configuration::Document::fromXML(const xmlpp::Element& element) {
  Section::fromXML(element);

  if (hasParameter("version")) {
    version = (*this)["version"].getValue();
    removeParameter("version");
  }
}

void Pololu::Configuration::Document::toXML(xmlpp::Document& document) const {
  document.add_comment("Document format: "PROJECT_NAME
    " configuration file (version "PROJECT_VERSION")");

  Section::toXML(document);
}

void Pololu::Configuration::Document::toXML(xmlpp::Element& element) const {
  element.set_attribute("version", version);
  Section::toXML(element);
}
