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

#ifndef POLOLU_CONFIG_SECTION_H
#define POLOLU_CONFIG_SECTION_H

/** \file section.h
  * \brief Pololu configuration section
  */

#include <map>

#include "config/parameter.h"

namespace xmlpp {
  class Document;
  class Element;
};

namespace Configuration {
  class Section {
  public:
    /** Construct a configuration section
      */
    Section(const std::string& name = "");
    Section(const Section& src);

    /** Destroy a configuration section
      */
    virtual ~Section();

    /** Access the name of the section
      */
    const std::string& getName() const;

    /** Access the subsection with the specified name
      */
    Section& getSection(const std::string& locator);
    const Section& getSection(const std::string& locator) const;

    Section& operator()(const std::string& locator);
    const Section& operator()(const std::string& locator) const;

    /** Access the parameter with the specified name
      */
    Parameter& getParameter(const std::string& locator);
    const Parameter& getParameter(const std::string& locator) const;

    Parameter& operator[](const std::string& locator);
    const Parameter& operator[](const std::string& locator) const;

    /** Configuration section assignments
      */
    Section& operator=(const Section& src);

    /** Read the configuration section from the given stream
      */
    void read(std::istream& stream);

    /** Write the configuration section to the given stream
      */
    void write(std::ostream& stream) const;

    /** Configuration section manipulations
      */
    Section& removeSection(const std::string& name);
    Section& removeParameter(const std::string& name);

    /** Configuration section queries
      */
    bool hasSection(const std::string& name) const;
    bool hasParameter(const std::string& name) const;

    /** Clear the configuration section
      */
    virtual Section& clear();
  protected:
    std::string name;

    std::map<std::string, Section> sections;
    std::map<std::string, Parameter> parameters;

    /** Pololu configuration section conversions
      */
    virtual void fromDocument(const xmlpp::Document& document);
    virtual void toDocument(xmlpp::Document& document) const;

    virtual void fromElement(const xmlpp::Element& element);
    virtual void toElement(xmlpp::Element& element) const;
  };
};

std::istream& operator>>(std::istream& stream, Configuration::Section& section);
std::ostream& operator<<(std::ostream& stream, const Configuration::Section&
  section);

#endif
