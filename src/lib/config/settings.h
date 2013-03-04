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

#ifndef POLOLU_CONFIG_SETTINGS_H
#define POLOLU_CONFIG_SETTINGS_H

/** \file settings.h
  * \brief Pololu settings class
  */

#include <iostream>

#include "config/section.h"

namespace Configuration {
  class Settings :
    public Section {
  public:
    /** Construct a settings object
      */
    Settings(const std::string& name = "", const std::string&
      version = "1");
    Settings(const Settings& src);

    /** Destroy a settings object
      */
    virtual ~Settings();

    /** Access the version of the settings
      */
    const std::string& getVersion() const;
    void setVersion(const std::string& version);

    /** Configuration assignments
      */
    Settings& operator=(const Settings& src);

    /** Load the settings from the file with the specified filename
      */
    void load(const std::string& filename);

    /** Save the settings to the file with the specified filename
      */
    void save(const std::string& filename) const;

    Settings& clear();
  protected:
    std::string version;

    void toDocument(xmlpp::Document& document) const;

    void fromElement(const xmlpp::Element& element);
    void toElement(xmlpp::Element& element) const;
  };
};

#endif
