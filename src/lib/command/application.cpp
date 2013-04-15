/***************************************************************************
 *   Copyright (C) 2013 by Ralf Kaestner                                   *
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

#include <iomanip>

#include "base/singleton.h"

#include "application.h"

#include "config.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Command::Application::DefaultKeyedArguments::DefaultKeyedArguments() {
  (*this)["help"] = Argument("Display usage and exit", "", false);
  (*this)["version"] = Argument("Display version and exit", "", false);
}

Pololu::Command::Application::ArgumentIndexError::ArgumentIndexError(
    int index) :
  Exception("Invalid argument index: %d", index) {
}

Pololu::Command::Application::ArgumentKeyError::ArgumentKeyError(const
    std::string& key) :
  Exception("Invalid argument key: %s", key.c_str()) {
}

Pololu::Command::Application::ArgumentFormatError::ArgumentFormatError(const
    std::string& key, const std::string& format) :
  Exception("Argument format error: --%s %s", key.c_str(), format.c_str()) {
}

Pololu::Command::Application::UnexpectedArgumentError::UnexpectedArgumentError(
    const std::string& argument) :
  Exception("Unexpected argument: %s", argument.c_str()) {
}

Pololu::Command::Application::MissingArgumentError::MissingArgumentError(
    const std::string& format) :
  Exception("Missing argument: %s", format.c_str()) {
}

Pololu::Command::Application::Application(const std::string& description) :
  description(description),
  keyedArguments(Singleton<DefaultKeyedArguments>::getInstance()) {
}

Pololu::Command::Application::Application(const Application& src) :
  description(src.description),
  executable(src.executable),
  keyedArguments(src.keyedArguments),
  arguments(src.arguments) {
}

Pololu::Command::Application::~Application() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

const std::string& Pololu::Command::Application::getDescription() const {
  return description;
}

const std::string& Pololu::Command::Application::getExecutable() const {
  return executable;
}

Pololu::Command::Argument& Pololu::Command::Application::operator[](
    int index) {
  if (index == arguments.size())
    arguments.resize(arguments.size()+1);

  if ((index >= 0) && (index < arguments.size()))
    return arguments[index];
  else
    throw ArgumentIndexError(index);
}

const Pololu::Command::Argument& Pololu::Command::Application::operator[](
    int index) const {
  if ((index >= 0) && (index < arguments.size()))
    return arguments[index];
  else
    throw ArgumentIndexError(index);
}

Pololu::Command::Argument& Pololu::Command::Application::operator[](
    const std::string& key) {
  return keyedArguments[key];
}

const Pololu::Command::Argument& Pololu::Command::Application::operator[](
    const std::string& key) const {
  std::map<std::string, Argument>::const_iterator
    it = keyedArguments.find(key);

  if (it != keyedArguments.end())
    return it->second;
  else
    throw ArgumentKeyError(key);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Command::Application& Pololu::Command::Application::operator=(const
    Application& src) {
  description = src.description;
  executable = src.executable;

  arguments = src.arguments;
  keyedArguments = src.keyedArguments;

  return *this;
}

void Pololu::Command::Application::addArgument(const Argument& argument) {
  arguments.push_back(argument);
}

void Pololu::Command::Application::addArgument(const std::string& key, const
    Argument& argument) {
  std::map<std::string, Argument>::iterator it = keyedArguments.find(key);

  if (it == keyedArguments.end()) {
    it = keyedArguments.insert(std::make_pair(key, argument)).first;
    if (it->second.getValue().empty())
      it->second.setValue<bool>(false);
  }
  else
    throw ArgumentKeyError(key);
}

bool Pololu::Command::Application::parseArguments(size_t argc, char** argv) {
  std::string argument = argv[0];

  size_t i = argument.rfind('/');
  if (i != std::string::npos)
    executable = argument.substr(i+1);
  else
    executable = argument;

  int j = 0;
  for (int i = 1; i < argc; ++i) {
    argument = argv[i];

    if ((argument[0] == '-') && (argument[1] == '-')) {
      std::string key = argument.substr(2);

      std::map<std::string, Argument>::iterator it = keyedArguments.find(key);
      if (it != keyedArguments.end()) {
        if (it->second.getFormat().empty()) {
          it->second.setValue<bool>(true);

          if ((*this)["help"].getValue<bool>()) {
            writeHelp(std::cerr);
            return false;
          }

          if ((*this)["version"].getValue<bool>()) {
            writeVersion(std::cout);
            return false;
          }
        }
        else if (i+1 < argc) {
          std::string value = argv[++i];
          it->second.setValue(value);
        }
        else
          throw ArgumentFormatError(key, it->second.getFormat());
      }
      else
        throw ArgumentKeyError(key);
    }
    else {
      if (j < arguments.size()) {
        if (arguments[j].getGreedy()) {
          std::string args;
          for ( ; i < argc; ++i) {
            args += argv[i];
            if (i+1 < argc)
              args += " ";
          }

          arguments[j].setValue(args);
        }
        else {
          arguments[j].setValue(argument);
          ++j;
        }
      }
      else
        throw UnexpectedArgumentError(argument);
    }
  }

  for ( ; j < arguments.size(); ++j)
    if (arguments[j].getValue().empty())
      throw MissingArgumentError(arguments[j].getFormat());

  return true;
}

void Pololu::Command::Application::writeHelp(std::ostream& stream) const {
  stream << "Usage: " << executable;
  if (!keyedArguments.empty())
    stream << " [OPT1 [OPT2 [...]]]";
  for (int i = 0; i < arguments.size(); ++i) {
    if (arguments[i].getValue().empty())
      stream << " ";
    else
      stream << " [";

    if (arguments[i].getGreedy())
      stream << arguments[i].getFormat() << "1 [" <<
        arguments[i].getFormat() << "2...]";
    else
      stream << arguments[i].getFormat();

    if (!arguments[i].getValue().empty())
      stream << "]";

    if (arguments[i].getGreedy())
      break;
  }
  stream << std::endl;

  stream << "\033[1m" << description << "\033[0m" << std::endl;

  for (int i = 0; i < arguments.size(); ++i) {
    stream << "  " << std::setw(28) << std::setfill(' ') << std::left;
    if (arguments[i].getGreedy())
      stream << arguments[i].getFormat()+"1 "+arguments[i].getFormat()+"2...";
    else
      stream << arguments[i].getFormat();
    stream << arguments[i].getDescription() << std::endl;
  }
  if (!keyedArguments.empty())
    stream << "  " << std::setw(28) << std::setfill(' ') << std::left <<
      "OPT1 OPT2..." << "List of options as given below [default]" << std::endl;

  for (std::map<std::string, Argument>::const_iterator
      it = keyedArguments.begin(); it != keyedArguments.end(); ++it) {
    std::string format = "--"+it->first+" "+it->second.getFormat();
    stream << "  " << std::setw(28) << std::setfill(' ') << std::left <<
      format << it->second.getDescription();
    if (!it->second.getFormat().empty() && !it->second.getValue().empty())
      stream << " [" << it->second.getValue() << "]";
    stream << std::endl;
  }

  stream << "Report bugs to <" << PROJECT_CONTACT <<
    ">, attach error logs" << std::endl;
}

void Pololu::Command::Application::writeVersion(std::ostream& stream) const {
  stream << PROJECT_NAME << " " << PROJECT_VERSION << " (" <<
    PROJECT_RELEASE << ") [Build: " << PROJECT_BUILD_TYPE << " on " <<
    PROJECT_BUILD_SYSTEM << " " << PROJECT_BUILD_ARCH << "]" << std::endl;
}
