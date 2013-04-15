/***************************************************************************
 *   Copyright (C) 2013 by Ralf Kaestner                                   *
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

#include <libxml++/libxml++.h>

#include "section.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Configuration::Section::FormatError::FormatError() :
  Exception("Invalid configuration document format") {
}

Pololu::Configuration::Section::SectionError::SectionError(const
    std::string& name) :
  Exception("Invalid configuration section: %s", name.c_str()) {
}

Pololu::Configuration::Section::ParameterError::ParameterError(const
    std::string& name) :
  Exception("Invalid configuration parameter: %s", name.c_str()) {
}

Pololu::Configuration::Section::Section(const std::string& name) :
  name(name) {
}

Pololu::Configuration::Section::Section(const Section& src) :
  name(src.name),
  sections(src.sections),
  parameters(src.parameters) {
}

Pololu::Configuration::Section::~Section() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const std::string& Pololu::Configuration::Section::getName() const {
  return name;
}

Pololu::Configuration::Section& Pololu::Configuration::Section::getSection(
    const std::string& location) {
  std::string name = location, sublocation;

  int i = location.find("/");
  if (i >= 0) {
    name = location.substr(0, i);
    sublocation = location.substr(i+1);
  }

  std::map<std::string, Section>::iterator it = sections.find(name);

  if (it == sections.end())
    it = sections.insert(std::make_pair(name, name));

  if (sublocation.empty())
    return it->second;
  else
    return it->second(sublocation);
}

const Pololu::Configuration::Section&
    Pololu::Configuration::Section::getSection(const std::string& location)
    const {
  std::string name = location, sublocation;

  int i = location.find("/");
  if (i >= 0) {
    name = location.substr(0, i);
    sublocation = location.substr(i+1);
  }

  std::map<std::string, Section>::const_iterator it = sections.find(name);

  if (it != sections.end()) {
    if (sublocation.empty())
      return it->second;
    else
      return it->second(sublocation);
  }
  else
    throw SectionError(name);
}

std::list<const Pololu::Configuration::Section*>
    Pololu::Configuration::Section::getSections(const std::string&
    location) const {
  std::list<const Section*> sections;
  std::string name = location, sublocation;

  int i = location.find("/");
  if (i >= 0) {
    name = location.substr(0, i);
    sublocation = location.substr(i+1);
  }

  std::pair<std::map<std::string, Section>::const_iterator,
    std::map<std::string, Section>::const_iterator> range =
    this->sections.equal_range(name);

  for (std::map<std::string, Section>::const_iterator it = range.first;
      it != range.second; ++it) {
    if (!sublocation.empty()) {
      std::list<const Section*> subsections =
        it->second.getSections(sublocation);
      sections.insert(sections.end(), subsections.begin(),
        subsections.end());
    }
    else
      sections.push_back(const_cast<Section*>(&it->second));
  }

  return sections;
}

Pololu::Configuration::Section& Pololu::Configuration::Section::operator()(
    const std::string& location) {
  return getSection(location);
}

const Pololu::Configuration::Section&
    Pololu::Configuration::Section::operator()(const std::string& location)
    const {
  return getSection(location);
}

Pololu::Configuration::Parameter&
    Pololu::Configuration::Section::getParameter(const std::string&
    location) {
  std::string name = location, sublocation;

  int i = location.find("/");
  if (i >= 0) {
    name = location.substr(0, i);
    sublocation = location.substr(i+1);
  }

  if (sublocation.empty())
    return parameters[name];
  else
    return (*this)(name)[sublocation];
}

const Pololu::Configuration::Parameter&
    Pololu::Configuration::Section::getParameter(const std::string& location)
    const {
  std::string name = location, sublocation;

  int i = location.find("/");
  if (i >= 0) {
    name = location.substr(0, i);
    sublocation = location.substr(i+1);
  }

  if (sublocation.empty()) {
    std::map<std::string, Parameter>::const_iterator
      it = parameters.find(name);

    if (it != parameters.end())
      return it->second;
    else
      throw ParameterError(name);
  }
  else
    return (*this)(name)[sublocation];
}

Pololu::Configuration::Parameter& Pololu::Configuration::Section::operator[](
    const std::string& location) {
  return getParameter(location);
}

const Pololu::Configuration::Parameter&
    Pololu::Configuration::Section::operator[](const std::string& location)
    const {
  return getParameter(location);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Configuration::Section& Pololu::Configuration::Section::operator=(
    const Section& src) {
  name = src.name;
  
  sections = src.sections;
  parameters = src.parameters;

  return *this;
}

Pololu::Configuration::Section& Pololu::Configuration::Section::clear() {
  name.clear();

  sections.clear();
  parameters.clear();

  return *this;
}

void Pololu::Configuration::Section::read(std::istream& stream) {
  xmlpp::DomParser parser;

  clear();
  parser.parse_stream(stream);

  xmlpp::Document* document = parser.get_document();

  if (document)
    fromXML(*document);
  else
    throw FormatError();
}

void Pololu::Configuration::Section::write(std::ostream& stream) const {
  xmlpp::Document document;

  toXML(document);
  document.write_to_stream_formatted(stream);
}

Pololu::Configuration::Section& Pololu::Configuration::Section::addSection(
    const std::string& name) {
  return sections.insert(std::make_pair(name, name))->second;
}

Pololu::Configuration::Section& Pololu::Configuration::Section::removeSection(
    const std::string& name) {
  std::map<std::string, Section>::iterator it = sections.find(name);

  if (it != sections.end())
    sections.erase(it);
  else
    throw SectionError(name);
}

Pololu::Configuration::Section&
    Pololu::Configuration::Section::removeParameter(const std::string&
    name) {
  std::map<std::string, Parameter>::iterator it = parameters.find(name);

  if (it != parameters.end())
    parameters.erase(it);
  else
    throw ParameterError(name);
}

bool Pololu::Configuration::Section::hasSection(const std::string& name)
    const {
  return sections.find(name) != sections.end();
}

bool Pololu::Configuration::Section::hasParameter(const std::string& name)
    const {
  return parameters.find(name) != parameters.end();
}

void Pololu::Configuration::Section::fromXML(const xmlpp::Document&
    document) {
  xmlpp::Element* root = document.get_root_node();

  if (root)
    fromXML(*root);
  else
    throw FormatError();
}

void Pololu::Configuration::Section::fromXML(const xmlpp::Element& element) {
  name = element.get_name();

  xmlpp::Element::AttributeList attributes = element.get_attributes();
  xmlpp::Element::NodeList children = element.get_children();

  for (xmlpp::Element::AttributeList::const_iterator
      it = attributes.begin(); it != attributes.end(); ++it)
    (*this)[(*it)->get_name()] = (*it)->get_value();

  for (xmlpp::Element::NodeList::const_iterator
    it = children.begin(); it != children.end(); ++it)
      if (((*it)->get_name() != "comment") && ((*it)->get_name() != "text")) {
    const xmlpp::Element* child = (const xmlpp::Element*)(*it);
    const xmlpp::TextNode* text = child->get_child_text();

    if (!text || text->is_white_space())
      addSection(child->get_name()).fromXML(*child);
    else
      (*this)[child->get_name()] = text->get_content();
  }
}

void Pololu::Configuration::Section::toXML(xmlpp::Document& document) const {
  xmlpp::Element* root = document.create_root_node(name);
  toXML(*root);
}

void Pololu::Configuration::Section::toXML(xmlpp::Element& element) const {
  element.set_name(name);

  for (std::map<std::string, Parameter>::const_iterator
      it = parameters.begin(); it != parameters.end(); ++it) {
    if (parameters.size() > 2)
      element.add_child(it->first)->add_child_text(it->second.getValue());
    else
      element.set_attribute(it->first, it->second);
  }

  for (std::map<std::string, Section>::const_iterator
      it = sections.begin(); it != sections.end(); ++it)
    it->second.toXML(*element.add_child(it->first));
}

std::istream& operator>>(std::istream& stream,
    Pololu::Configuration::Section& section) {
  section.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Configuration::Section& section) {
  section.write(stream);
  return stream;
}
