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

#ifndef POLOLU_CONFIGURATION_H
#define POLOLU_CONFIGURATION_H

/** \file configuration.h
  * \brief Pololu configuration class
  */

#include <iostream>

#include "config/section.h"

class PololuConfiguration :
  public PololuSection {
public:
  /** Construct a Pololu configuration object
    */
  PololuConfiguration(const char* filename = 0);
  PololuConfiguration(const PololuConfiguration& src);

  /** Destroy a Pololu configuration object
    */
  virtual ~PololuConfiguration();

  /** Pololu configuration assignments
    */
  PololuConfiguration& operator=(const PololuConfiguration& src);

  /** Load the Pololu configuration from the file with the specified
    * filename
    */
  void load(const char* filename);
  /** Load the Pololu configuration from the given stream
    */
  void load(std::istream& stream);

  /** Save the Pololu configuration to the file with the specified
    * filename
    */
  void save(const char* filename) const;
  /** Save the Pololu configuration to the given stream
    */
  void save(std::ostream& stream) const;
};

#endif
