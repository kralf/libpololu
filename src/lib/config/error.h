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

#ifndef POLOLU_USB_ERROR_H
#define POLOLU_USB_ERROR_H

/** \file error.h
  * \brief Pololu USB error
  */

#include <stdexcept>
#include <map>
#include <string>

namespace USB {
  class Error :
    public std::exception {
  public:
    /** Types and non-static subclasses
      */
    class Strings : public std::map<int, std::string> {
    public:
      /** Constructors
        */
      Strings();
    };

    /** Construct a USB error
      */
    Error(const std::string& what, int error);
    Error(const Error& src);

    /** Destroy a USB error
      */
    virtual ~Error() throw();

    /** USB error assignments
      */
    Error& operator=(const Error& src);

    /** USB error assertion
      */
    static void assert(const std::string& what, int error);

    const char* what() const throw();
  protected:
    static const Strings strings;

    int error;

    std::string description;
  };
};

#endif
