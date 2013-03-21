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

#ifndef POLOLU_COMMAND_APPLICATION_H
#define POLOLU_COMMAND_APPLICATION_H

/** \file application.h
  * \brief Pololu commandline application
  */

#include <vector>
#include <map>
#include <iostream>

#include "command/argument.h"

namespace Pololu {
  namespace Command {
    class Application :
      public Pololu::Object {
    public:
      /** Types and non-static subclasses
        */
      class DefaultKeyedArguments :
        public std::map<std::string, Argument> {
      public:
        /** Construct a commandline default keyed arguments object
          */
        DefaultKeyedArguments();
      };

      class ArgumentIndexError :
        public Exception {
      public:
        /** Construct a commandline argument index error
          */
        ArgumentIndexError(int index);
      };

      class ArgumentKeyError :
        public Exception {
      public:
        /** Construct a commandline argument key error
          */
        ArgumentKeyError(const std::string& key);
      };

      class ArgumentFormatError :
        public Exception {
      public:
        /** Construct a commandline argument format error
          */
        ArgumentFormatError(const std::string& key, const
          std::string& format);
      };

      class UnexpectedArgumentError :
        public Exception {
      public:
        /** Construct a commandline unexpected argument error
          */
        UnexpectedArgumentError(const std::string& argument);
      };

      class MissingArgumentError :
        public Exception {
      public:
        /** Construct a commandline missing argument error
          */
        MissingArgumentError(const std::string& format);
      };

      /** Construct a Pololu commandline application
        */
      Application(const std::string& description);
      Application(const Application& src);

      /** Destroy a Pololu commandline application
        */
      virtual ~Application();

      /** Pololu commandline application assignments
        */
      Application& operator=(const Application& src);

      /** Access the description of the commandline application
        */
      const std::string& getDescription() const;
      /** Access the executable of the commandline application
        */
      const std::string& getExecutable() const;

      /** Access the commandline argument with the specified index
        */
      Argument& operator[](int index);
      const Argument& operator[](int index) const;
      /** Access the commandline argument with the specified key
        */
      Argument& operator[](const std::string& key);
      const Argument& operator[](const std::string& key) const;

      /** Add an argument to the Pololu commandline application
        */
      void addArgument(const Argument& argument);
      void addArgument(const std::string& key, const Argument& argument);

      /** Parse the commandline arguments
        */
      bool parseArguments(size_t argc, char** argv);

      /** Write the commandline application's help to the given stream
        */
      void writeHelp(std::ostream& stream) const;
      /** Write the commandline application's version to the given stream
        */
      void writeVersion(std::ostream& stream) const;
    protected:
      std::string description;
      std::string executable;

      std::vector<Argument> arguments;
      std::map<std::string, Argument> keyedArguments;
    };
  };
};

#endif
