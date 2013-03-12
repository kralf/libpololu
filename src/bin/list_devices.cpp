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

#include <iostream>

#include "pololu.h"

using namespace Pololu;

int main(int argc, char **argv) {
  std::list<Pointer<Device> > devices = discoverDevices();

  if (!devices.empty()) {
    for (std::list<Pointer<Device> >::const_iterator it = devices.begin();
        it != devices.end(); ++it)
      std::cout << **it << " on " << (*it)->getInterface()->getFullName() <<
        " interface " << *(*it)->getInterface() << std::endl;
  }
  else
    std::cout << "No devices found." << std::endl;

  return 0;
}
