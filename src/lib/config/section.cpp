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

#include <libxml++/libxml++.h>

#include "section.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Configuration::Section::Section(const std::string& name) :
  name(name) {
}

Configuration::Section::Section(const Configuration::Section&
src) :
  name(src.name),
  sections(src.sections),
  parameters(src.parameters) {
}

Configuration::Section::~Section() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const std::string& Configuration::Section::getName() const {
  return name;
}

Configuration::Section& Configuration::Section::getSection(const std::string&
    locator) {
  std::string name = locator, sublocator;

  int i = locator.find("/");
  if (i >= 0) {
    name = locator.substr(0, i);
    sublocator = locator.substr(i+1);
  }

  std::map<std::string, Configuration::Section>::iterator
    it = sections.find(name);

  if (it == sections.end()) {
    Configuration::Section section(name);
    it = sections.insert(std::make_pair(name, section)).first;
  }

  if (sublocator.empty())
    return it->second;
  else
    return it->second(sublocator);
}

const Configuration::Section& Configuration::Section::getSection(const
    std::string& locator) const {
  std::string name = locator, sublocator;

  int i = locator.find("/");
  if (i >= 0) {
    name = locator.substr(0, i);
    sublocator = locator.substr(i+1);
  }

  std::map<std::string, Configuration::Section>::const_iterator
    it = sections.find(name);

  if (it != sections.end()) {
    if (sublocator.empty())
      return it->second;
    else
      return it->second(sublocator);
  }
  else
    PololuUtils::error("Bad configuration section", name);
}

Configuration::Section& Configuration::Section::operator()(const std::string&
    locator) {
  return getSection(locator);
}

const Configuration::Section& Configuration::Section::operator()(const
    std::string& locator) const {
  return getSection(locator);
}

Configuration::Parameter& Configuration::Section::getParameter(const
    std::string& locator) {
  std::string name = locator, sublocator;

  int i = locator.find("/");
  if (i >= 0) {
    name = locator.substr(0, i);
    sublocator = locator.substr(i+1);
  }

  if (sublocator.empty())
    return parameters[name];
  else
    return (*this)(name)[sublocator];
}

const Configuration::Parameter& Configuration::Section::getParameter(const
    std::string& locator) const {
  std::string name = locator, sublocator;

  int i = locator.find("/");
  if (i >= 0) {
    name = locator.substr(0, i);
    sublocator = locator.substr(i+1);
  }

  if (sublocator.empty()) {
    std::map<std::string, Configuration::Parameter>::const_iterator
      it = parameters.find(locator);

    if (it != parameters.end())
      return it->second;
    else
      PololuUtils::error("Bad configuration parameter", locator);
  }
  else
    return (*this)(name)[sublocator];
}

Configuration::Parameter& Configuration::Section::operator[](const
    std::string& locator) {
  return getParameter(locator);
}

const Configuration::Parameter& Configuration::Section::operator[](const
    std::string& locator) const {
  return getParameter(locator);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Configuration::Section& Configuration::Section::operator=(const
    Configuration::Section& src) {
  name = src.name;
  
  sections = src.sections;
  parameters = src.parameters;

  return *this;
}

Configuration::Section& Configuration::Section::clear() {
  name.clear();

  sections.clear();
  parameters.clear();

  return *this;
}

void Configuration::Section::read(std::istream& stream) {
  xmlpp::DomParser parser;

  clear();
  parser.parse_stream(stream);

  xmlpp::Document* document = parser.get_document();

  if (document)
    fromDocument(*document);
  else
    PololuUtils::error("Read error", "Invalid XML document");
}

void Configuration::Section::write(std::ostream& stream) const {
  xmlpp::Document document;

  toDocument(document);
  document.write_to_stream_formatted(stream);
}

Configuration::Section& Configuration::Section::removeSection(const
    std::string& name) {
  std::map<std::string, Configuration::Section>::iterator it =
sections.find(name);

  if (it != sections.end())
    sections.erase(it);
  else
    PololuUtils::error("Bad configuration section", name);
}

Configuration::Section& Configuration::Section::removeParameter(const
    std::string& name) {
  std::map<std::string, Configuration::Parameter>::iterator
    it = parameters.find(name);

  if (it != parameters.end())
    parameters.erase(it);
  else
    PololuUtils::error("Bad configuration parameter", name);
}

bool Configuration::Section::hasSection(const std::string& name) const {
  return sections.find(name) != sections.end();
}

bool Configuration::Section::hasParameter(const std::string& name) const {
  return parameters.find(name) != parameters.end();
}

void Configuration::Section::fromDocument(const xmlpp::Document& document) {
  xmlpp::Element* root = document.get_root_node();

  if (root)
    fromElement(*root);
  else
    PololuUtils::error("Read error", "Missing XML root node");
}

void Configuration::Section::toDocument(xmlpp::Document& document) const {
  xmlpp::Element* root = document.create_root_node(name);
  toElement(*root);
}

void Configuration::Section::fromElement(const xmlpp::Element& element) {
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
      (*this)(child->get_name()).fromElement(*child);
    else
      (*this)[child->get_name()] = text->get_content();
  }
}

void Configuration::Section::toElement(xmlpp::Element& element) const {
  element.set_name(name);

  for (std::map<std::string, Configuration::Parameter>::const_iterator
      it = parameters.begin(); it != parameters.end(); ++it) {
    if (parameters.size() > 2)
      element.add_child(it->first)->add_child_text(it->second.getValue());
    else
      element.set_attribute(it->first, it->second);
  }

  for (std::map<std::string, Configuration::Section>::const_iterator
      it = sections.begin(); it != sections.end(); ++it)
    it->second.toElement(*element.add_child(it->first));
}

std::istream& operator>>(std::istream& stream, Configuration::Section&
    section) {
  section.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Configuration::Section&
    section) {
  section.write(stream);
  return stream;
}
