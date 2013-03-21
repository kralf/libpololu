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

#include "protocol.h"

#include "getfirmwareversion.h"
#include "startbootloader.h"
#include "restoresettings.h"
#include "getsettings.h"
#include "setmotorlimit.h"
#include "exitsafestart.h"
#include "setsettings.h"
#include "getvariables.h"
#include "getresetflags.h"
#include "setusbkill.h"
#include "setspeed.h"
#include "setbrake.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::Protocol::Protocol() {
  requests["GetFirmwareVersion"] = new GetFirmwareVersion();
  requests["StartBootloader"] = new StartBootloader();
  requests["RestoreSettings"] = new RestoreSettings();
  requests["GetSettings"] = new GetSettings();
  requests["SetMotorLimit"] = new SetMotorLimit();
  requests["ExitSafeStart"] = new ExitSafeStart();
  requests["SetSettings"] = new SetSettings();
  requests["GetVariables"] = new GetVariables();
  requests["GetResetFlags"] = new GetResetFlags();
  requests["SetUsbKill"] = new SetUsbKill();
  requests["SetSpeed"] = new SetSpeed();
  requests["SetBrake"] = new SetBrake();
}

Pololu::Smc::Usb::Protocol::Protocol(const Protocol& src) :
  Pololu::Usb::Protocol(src) {
}

Pololu::Smc::Usb::Protocol::~Protocol() {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Smc::Usb::Protocol& Pololu::Smc::Usb::Protocol::operator=(const
    Protocol& src) {
  Pololu::Usb::Protocol::operator=(src);
  return *this;
}

Pololu::Smc::Usb::Protocol* Pololu::Smc::Usb::Protocol::clone() const {
  return new Protocol(*this);
}
