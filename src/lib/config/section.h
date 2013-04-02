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

#include <iostream>
#include <map>
#include <list>

#include "config/parameter.h"

#include "base/exception.h"

namespace xmlpp {
  class Document;
  class Element;
};

namespace Pololu {
  namespace Configuration {
    class Section :
      public Pololu::Object {
    public:
      /** Types and non-static subclasses
        */
      class FormatError :
        public Exception {
      public:
        /** Construct a section format error
          */
        FormatError();
      };

      class SectionError :
        public Exception {
      public:
        /** Construct a section error
          */
        SectionError(const std::string& name);
      };

      class ParameterError :
        public Exception {
      public:
        /** Construct a parameter error
          */
        ParameterError(const std::string& name);
      };

      /** Construct a Pololu configuration section
        */
      Section(const std::string& name = "");
      Section(const Section& src);

      /** Destroy a Pololu configuration section
        */
      virtual ~Section();

      /** Access the name of the section
        */
      const std::string& getName() const;

      /** Access the subsections at the specified location
        */
      Section& getSection(const std::string& location);
      const Section& getSection(const std::string& location) const;
      std::list<const Section*> getSections(const std::string&
        location) const;

      Section& operator()(const std::string& location);
      const Section& operator()(const std::string& location) const;

      /** Access the parameter at the specified location
        */
      Parameter& getParameter(const std::string& location);
      const Parameter& getParameter(const std::string& location) const;

      Parameter& operator[](const std::string& location);
      const Parameter& operator[](const std::string& location) const;

      /** Pololu configuration section assignments
        */
      Section& operator=(const Section& src);

      /** Read the configuration section from the given stream
        */
      void read(std::istream& stream);
      /** Write the configuration section to the given stream
        */
      void write(std::ostream& stream) const;

      /** Attempt to query the parameter at the specified location and
        * assign its value to the given variable if the parameter exists
        */
      template <typename T> bool query(const std::string& location,
        T& value) const;
      template <typename T, typename U> bool query(const std::string&
        location, T& value, const std::map<U, std::string>& values) const;

      /** Pololu configuration section manipulations
        */
      Section& addSection(const std::string& name);
      Section& removeSection(const std::string& name);
      Section& removeParameter(const std::string& name);

      /** Pololu configuration section queries
        */
      bool hasSection(const std::string& name) const;
      bool hasParameter(const std::string& name) const;

      /** Clear the configuration section
        */
      virtual Section& clear();
    protected:
      std::string name;

      std::multimap<std::string, Section> sections;
      std::map<std::string, Parameter> parameters;

      /** Pololu configuration section conversions
        */
      virtual void fromXML(const xmlpp::Document& document);
      virtual void fromXML(const xmlpp::Element& element);

      virtual void toXML(xmlpp::Element& element) const;
      virtual void toXML(xmlpp::Document& document) const;
    };
  };
};

std::istream& operator>>(std::istream& stream,
  Pololu::Configuration::Section& section);
std::ostream& operator<<(std::ostream& stream, const
  Pololu::Configuration::Section& section);

#include "config/section.tpp"

#endif
