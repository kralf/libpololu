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

#include "base/singleton.h"

#include "usc/device.h"

#include "protocol.h"

#include "getfirmwareversion.h"
#include "erasescript.h"
#include "restartscriptat.h"
#include "restartscriptatparam.h"
#include "restartscript.h"
#include "writescript.h"
#include "writesubroutines.h"
#include "setscriptstatus.h"
#include "startbootloader.h"
#include "reinitialize.h"
#include "clearerrors.h"
#include "settarget.h"
#include "setspeed.h"
#include "setacceleration.h"
#include "restoresettings.h"
#include "setmodulation.h"

#include "micro/getvariables.h"
#include "micro/getsettings.h"
#include "micro/setsettings.h"

#include "mini/getvariables.h"
#include "mini/getstack.h"
#include "mini/getcallstack.h"
#include "mini/getservovariables.h"
#include "mini/getsettings.h"
#include "mini/setsettings.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::Protocol::SubroutinesIndexes::SubroutinesIndexes() {
  (*this)[Device::typeMaestro6] = 64;
  (*this)[Device::typeMaestro6b] = 64;
  (*this)[Device::typeMaestro12] = 512;
  (*this)[Device::typeMaestro12b] = 512;
  (*this)[Device::typeMaestro18] = 512;
  (*this)[Device::typeMaestro18b] = 512;
  (*this)[Device::typeMaestro24] = 512;
  (*this)[Device::typeMaestro24b] = 512;
}

Pololu::Usc::Usb::Protocol::Protocol(Device::Type type) {
  requests["GetFirmwareVersion"] = new GetFirmwareVersion();
  requests["EraseScript"] = new EraseScript();
  requests["RestartScriptAt"] = new RestartScriptAt();
  requests["RestartScriptAtParam"] = new RestartScriptAtParam();
  requests["RestartScript"] = new RestartScript();
  requests["WriteScript"] = new WriteScript(
    Singleton<Device::MaxScriptSizes>::getInstance()[type]);
  requests["WriteSubroutines"] = new WriteSubroutines(
    Singleton<SubroutinesIndexes>::getInstance()[type]);
  requests["SetScriptStatus"] = new SetScriptStatus();
  requests["StartBootloader"] = new StartBootloader();
  requests["Reinitialize"] = new Reinitialize();
  requests["ClearErrors"] = new ClearErrors();
  requests["SetTarget"] = new SetTarget(
    Singleton<Device::NumChannels>::getInstance()[type]);
  requests["SetSpeed"] = new SetSpeed(
    Singleton<Device::NumChannels>::getInstance()[type]);
  requests["SetAcceleration"] = new SetAcceleration(
    Singleton<Device::NumChannels>::getInstance()[type]);
  requests["RestoreSettings"] = new RestoreSettings();
  requests["SetModulation"] = new SetModulation();

  Device::SuperType superType =
    Singleton<Device::SuperTypes>::getInstance()[type];

  if (superType == Device::superTypeMicro) {
    requests["GetVariables"] = new Micro::GetVariables();
    requests["GetSettings"] = new Micro::GetSettings();
    requests["SetSettings"] = new Micro::SetSettings();
  }
  else {
    requests["GetVariables"] = new Mini::GetVariables();
    requests["GetStack"] = new Mini::GetStack();
    requests["GetCallStack"] = new Mini::GetCallStack();
    requests["GetServoVariables"] = new Mini::GetServoVariables(
      Singleton<Device::NumChannels>::getInstance()[type]);
    requests["GetSettings"] = new Mini::GetSettings(
      Singleton<Device::NumChannels>::getInstance()[type]);
    requests["SetSettings"] = new Mini::SetSettings(
      Singleton<Device::NumChannels>::getInstance()[type]);
  }
}

Pololu::Usc::Usb::Protocol::Protocol(const Protocol& src) :
  Pololu::Usb::Protocol(src) {
}

Pololu::Usc::Usb::Protocol::~Protocol() {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::Protocol& Pololu::Usc::Usb::Protocol::operator=(const
    Protocol& src) {
  Pololu::Usb::Protocol::operator=(src);
  return *this;
}

Pololu::Usc::Usb::Protocol* Pololu::Usc::Usb::Protocol::clone() const {
  return new Protocol(*this);
}
