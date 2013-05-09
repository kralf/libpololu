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

#ifndef POLOLU_CONFIG_DOCUMENT_H
#define POLOLU_CONFIG_DOCUMENT_H

/** \brief Pololu configuration document class
  */

#include "config/section.h"

#include "base/exception.h"

namespace Pololu {
  namespace Configuration {
    class Document :
      public Section {
    public:
      /** Types and non-static subclasses
        */
      class FileError :
        public Exception {
      public:
        /** Construct a document file error
          */
        FileError(const std::string& filename);
      };

      /** Construct a Pololu configuration document object
        */
      Document(const std::string& name = "", const std::string&
        version = "1");
      Document(const Document& src);

      /** Destroy a Pololu configuration document object
        */
      virtual ~Document();

      /** Access the name of the document
        */
      void setName(const std::string& name);
      /** Access the version of the configuration document
        */
      const std::string& getVersion() const;
      void setVersion(const std::string& version);

      /** Pololu configuration document assignments
        */
      Document& operator=(const Document& src);

      /** Load the configuration document from the file with the specified
        * filename
        */
      void load(const std::string& filename);

      /** Save the configuration document to the file with the specified
        * filename
        */
      void save(const std::string& filename) const;

      Document& clear();
    protected:
      std::string version;

      /** Pololu configuration document conversions
        */
      void fromXML(const xmlpp::Element& element);

      void toXML(xmlpp::Document& document) const;
      void toXML(xmlpp::Element& element) const;
    };
  };
};

#endif
