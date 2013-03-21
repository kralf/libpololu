/***************************************************************************
 *   Copyright (C) 2010 by Ralf Kaestner and Luciano Spinello              *
 *   ralf.kaestner@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your argument) any later version.                                   *
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

#ifndef POLOLU_COMMAND_ARGUMENT_H
#define POLOLU_COMMAND_ARGUMENT_H

/** \file argument.h
  * \brief Pololu commandline argument
  */

#include "base/object.h"

namespace Pololu {
  namespace Command {
    class Argument {
    friend class Command;
    public:
      /** Construct a Pololu commandline argument
        */
      Argument(const std::string& description = "", const std::string&
        format = "", const char* value = "");
      template <typename T> Argument(const std::string& description,
        const std::string& format, const T& value);
      Argument(const Argument& src);

      /** Destroy a Pololu commandline argument
        */
      virtual ~Argument();

      /** Access the commandline argument's format
        */
      const std::string& getFormat() const;
      /** Access the commandline argument's value
        */
      const std::string& getValue() const;
      template <typename T> T getValue() const;
      void setValue(const std::string& value);
      template <typename T> void setValue(const T& value);
      /** Access the commandline argument's greedy flag
        */
      bool getGreedy() const;
      void setGreedy(bool greedy);

      /** Access the commandline argument's description
        */
      const std::string& getDescription() const;

      /** Pololu commandline argument assignments
        */
      template <typename T> Argument& operator=(const T& value);
      Argument& operator=(const Argument& src);
    protected:
      std::string format;
      std::string value;
      bool greedy;

      std::string description;
    };
  };
};

#include "command/argument.tpp"

#endif
