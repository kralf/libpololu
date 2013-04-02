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

#include "config/document.h"

#include "settings.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::Settings::SerialModes::SerialModes() {
  (*this)[serialModeUsbDualPort] = "USB_DUAL_PORT";
  (*this)[serialModeUsbChained] = "USB_CHAINED";
  (*this)[serialModeUartDetectBaudRate] = "UART_DETECT_BAUD_RATE";
  (*this)[serialModeUartFixedBaudRate] = "UART_FIXED_BAUD_RATE";
}

Pololu::Usc::Usb::Settings::Channel::Modes::Modes() {
  (*this)[modeServo] = "Servo";
  (*this)[modeServoMultiplied] = "ServoMultiplied";
  (*this)[modeOutput] = "Output";
  (*this)[modeInput] = "Input";
}

Pololu::Usc::Usb::Settings::Channel::HomeModes::HomeModes() {
  (*this)[homeModeOff] = "Off";
  (*this)[homeModeIgnore] = "Ignore";
  (*this)[homeModeGoto] = "Goto";
}

Pololu::Usc::Usb::Settings::Channel::Channel() :
  mode(modeServo),
  homeMode(homeModeOff),
  home(6000),
  minimum(3968),
  maximum(8000),
  neutral(6000),
  range(1905),
  speed(0),
  acceleration(0) {
}

Pololu::Usc::Usb::Settings::DocumentError::DocumentError(const
    std::string& name) :
  Exception("Invalid settings document: %s", name.c_str()) {
}

Pololu::Usc::Usb::Settings::ChannelError::ChannelError(unsigned char
    channel) :
  Exception("Invalid channel: %d", channel) {
}

Pololu::Usc::Usb::Settings::Settings(unsigned char numChannels) :
  serialMode(serialModeUartDetectBaudRate),
  fixedBaudRateRegister(Device::bpsToBaudRegister(9600)),
  enableCrc(false),
  neverSuspend(false),
  serialDeviceNumber(12),
  serialMiniSscOffset(0),
  serialTimeout(0),
  scriptStatus(Device::scriptStatusStopped),
  channels(numChannels) {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Usc::Usb::Settings::read(std::istream& stream) {
  Pololu::Configuration::Document document;
  stream >> document;

  if (document.getName() == "UscSettings")
    read(document);
  else
    throw DocumentError(document.getName());
}

void Pololu::Usc::Usb::Settings::write(std::ostream& stream) const {
  Pololu::Configuration::Document document("UscSettings");

  write(document);
  stream << document;
}

void Pololu::Usc::Usb::Settings::read(const Configuration::Section& section) {
  section.query("SerialMode", serialMode,
    Singleton<SerialModes>::getInstance());
  size_t fixedBaudRateBps = Device::baudRegisterToBps(fixedBaudRateRegister);
  section.query("FixedBaudRate", fixedBaudRateBps);
  fixedBaudRateRegister = Device::bpsToBaudRegister(fixedBaudRateBps);
  section.query("EnableCrc", enableCrc);
  section.query("NeverSuspend", neverSuspend);
  section.query("SerialDeviceNumber", serialDeviceNumber);
  section.query("SerialMiniSscOffset", serialMiniSscOffset);
  section.query("SerialTimeout", serialTimeout);
  bool scriptDone = (scriptStatus == Device::scriptStatusStopped);
  section.query("Script/ScriptDone", scriptDone);
  scriptStatus = scriptDone ? Device::scriptStatusStopped :
    Device::scriptStatusRunning;

  std::list<const Configuration::Section*> sections =
    section.getSections("Channels/Channel");
  int i = 0;
  for (std::list<const Configuration::Section*>::const_iterator
      it = sections.begin(); (i < channels.size()) && (it != sections.end());
      ++it, ++i) {
    (*it)->query("name", channels[i].name);
    (*it)->query("mode", channels[i].mode,
      Singleton<Channel::Modes>::getInstance());
    (*it)->query("homemode", channels[i].homeMode,
      Singleton<Channel::HomeModes>::getInstance());
    (*it)->query("home", channels[i].home);
    (*it)->query("min", channels[i].minimum);
    (*it)->query("max", channels[i].maximum);
    (*it)->query("neutral", channels[i].neutral);
    (*it)->query("range", channels[i].range);
    (*it)->query("speed", channels[i].speed);
    (*it)->query("acceleration", channels[i].acceleration);
  }
}

void Pololu::Usc::Usb::Settings::write(Configuration::Section& section)
    const {
  section["SerialMode"] = Singleton<SerialModes>::getInstance()[
    (SerialMode)serialMode];
  section["FixedBaudRate"] = Device::baudRegisterToBps(fixedBaudRateRegister);
  section["EnableCrc"] = enableCrc;
  section["NeverSuspend"] = neverSuspend;
  section["SerialDeviceNumber"] = serialDeviceNumber;
  section["SerialMiniSscOffset"] = serialMiniSscOffset;
  section["SerialTimeout"] = serialTimeout;       
  section["Script/ScriptDone"] = (scriptStatus == Device::scriptStatusStopped);

  for (int i = 0; i < channels.size(); ++i) {
    Pololu::Configuration::Section& subsection =
      section("Channels").addSection("Channel");

    subsection["name"] = channels[i].name;
    subsection["mode"] = Singleton<Channel::Modes>::getInstance()[
      channels[i].mode];
    subsection["homemode"] = Singleton<Channel::HomeModes>::getInstance()[
      channels[i].homeMode];
    subsection["home"] = channels[i].home;
    subsection["min"] = channels[i].minimum;
    subsection["max"] = channels[i].maximum;
    subsection["neutral"] = channels[i].neutral;
    subsection["range"] = channels[i].range;
    subsection["speed"] = channels[i].speed;
    subsection["acceleration"] = channels[i].acceleration;
  }
}

std::istream& operator>>(std::istream& stream,
    Pololu::Usc::Usb::Settings& settings) {
  settings.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Usc::Usb::Settings& settings) {
  settings.write(stream);
  return stream;
}
