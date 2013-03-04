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

#include "configuration.h"

#include "config.h"
#include "utils/utils.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

PololuConfiguration::PololuConfiguration(const char* filename) {
  if (filename)
    load(filename);
}

PololuConfiguration::PololuConfiguration(const PololuConfiguration& src) :
  PololuSection(src) {
}

PololuConfiguration::~PololuConfiguration() {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

PololuConfiguration& PololuConfiguration::operator=(const
    PololuConfiguration& src) {
  PololuSection::operator=(src);
  return *this;
}

void PololuConfiguration::load(const char* filename) {
  std::ifstream file(filename);

  if (!file.is_open())
    PololuUtils::error("Error opening configuration file for reading",
      filename);
  else
    load(file);
}

void PololuConfiguration::load(std::istream& stream) {
  xmlpp::DomParser parser;

  parser.parse_stream(stream);

  xmlpp::Document* document = parser.get_document();
}

void PololuConfiguration::save(const char* filename) const {
  std::ofstream file(filename);

  if (!file.is_open())
    PololuUtils::error("Error opening configuration file for writing",
      filename);
  else
    save(file);
}

void PololuConfiguration::save(std::ostream& stream) const {
  xmlpp::Document document;

  document.add_comment("Format: "PROJECT_NAME" configuration file (version "
    PROJECT_VERSION")");

  document.write_to_stream(stream);
}
