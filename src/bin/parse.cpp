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

#include <sstream>

#include "config/document.h"

#include "command/application.h"

using namespace Pololu;

int main(int argc, char **argv) {
  Command::Application application(
    "Parse Pololu configuration file");
  application[0] = Command::Argument(
    "Path to the configuration file", "FILENAME");
  application[1] = Command::Argument(
    "Name of the configuration section", "SECTION", "/");

  if (application.parseArguments(argc, argv)) {
    std::cout << "Parsing configuration file " <<
      application[0].getValue() << "..." << std::endl;

    Configuration::Document document;
    document.load(application[0].getValue());

    if (application[1].getValue() != "/")
      std::cout << const_cast<const Configuration::Document&>(document)(
        application[1].getValue());
    else
      std::cout << document;
  }

  return 0;
}
