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

#include "base/singleton.h"

#include "config/document.h"

#include "settings.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::Settings::CrcModes::CrcModes() {
  (*this)[crcModeDisabled] = "Disabled";
  (*this)[crcModeCommands] = "Commands";
  (*this)[crcModeCommandsAndResponses] = "CommandsAndResponses";
}

Pololu::Smc::Usb::Settings::InputModes::InputModes() {
  (*this)[inputModeSerialUsb] = "SerialUsb";
  (*this)[inputModeAnalog] = "Analog";
  (*this)[inputModeRc] = "RC";
}

Pololu::Smc::Usb::Settings::PwmModes::PwmModes() {
  (*this)[pwmModeDriveBrake] = "DriveBrake";
  (*this)[pwmModeDriveCoast] = "DriveCoast";
}

Pololu::Smc::Usb::Settings::MixingModes::MixingModes() {
  (*this)[mixingModeNone] = "None";
  (*this)[mixingModeLeft] = "Left";
  (*this)[mixingModeRight] = "Right";
}

Pololu::Smc::Usb::Settings::SerialModes::SerialModes() {
  (*this)[serialModeBinary] = "Binary";
  (*this)[serialModeAscii] = "Ascii";
}

Pololu::Smc::Usb::Settings::InputChannel::AlternateUses::AlternateUses() {
  (*this)[alternateUseNone] = "None";
  (*this)[alternateUseLimitForward] = "LimitForward";
  (*this)[alternateUseLimitReverse] = "LimitReverse";
  (*this)[alternateUseKillSwitch] = "KillSwitch";
}

Pololu::Smc::Usb::Settings::InputChannel::PinModes::PinModes() {
  (*this)[pinModeFloating] = "Floating";
  (*this)[pinModePullUp] = "PullUp";
  (*this)[pinModePullDown] = "PullDown";
}

Pololu::Smc::Usb::Settings::InputChannel::InputChannel() :
  invert(false),
  scalingDegree(0),
  alternateUse(alternateUseNone),
  pinMode(pinModeFloating),
  errorMin(500*4),
  errorMax(2500*4),
  inputMin(1000*4),
  inputMax(2000*4),
  inputNeutralMin(1475*4),
  inputNeutralMax(1525*4) {
}

Pololu::Smc::Usb::Settings::MotorLimits::MotorLimits() :
  maxSpeed(3200),
  maxAcceleration(0),
  maxDeceleration(0),
  brakeDuration(0),
  startingSpeed(0),
  reserved0(0) {
}

Pololu::Smc::Usb::Settings::DocumentError::DocumentError(const
    std::string& name) :
  Exception("Invalid settings document: %s", name.c_str()) {
}

Pololu::Smc::Usb::Settings::Settings() :
  neverSuspend(false),
  uartResponseDelay(false),
  useFixedBaudRate(false),
  disableSafeStart(false),
  fixedBaudRateRegister(Device::bpsToBaudRegister(9600)),
  speedUpdatePeriod(1),
  commandTimeout(0),
  serialDeviceNumber(13),
  crcMode(crcModeDisabled),
  overTempMin(70*10),
  overTempMax(80*10),
  inputMode(inputModeSerialUsb),
  pwmMode(pwmModeDriveBrake),
  pwmPeriodFactor(0),
  mixingMode(mixingModeNone),
  minPulsePeriod(9),
  maxPulsePeriod(100),
  rcTimeout(500),
  ignorePotDisconnect(false),
  tempLimitGradual(false),
  consecGoodPulses(2),
  motorInvert(false),
  speedZeroBrakeAmount(32),
  ignoreErrLineHigh(false),
  vinMultiplierOffset(0),
  lowVinShutoffTimeout(250),
  lowVinShutoffMv(5500),
  lowVinStartupMv(6000),
  highVinShutoffMv(25000),
  serialMode(serialModeBinary),
  reserved0(0) {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Smc::Usb::Settings::read(std::istream& stream) {
  Pololu::Configuration::Document document;
  stream >> document;

  if (document.getName() != "SmcSettings")
    throw DocumentError(document.getName());

  document.query("NeverSuspend", neverSuspend);
  document.query("UartResponseDelay", uartResponseDelay);
  document.query("UseFixedBaudRate", useFixedBaudRate);
  document.query("DisableSafeStart", disableSafeStart);
  size_t fixedBaudRateBps = Device::baudRegisterToBps(fixedBaudRateRegister);
  document.query("FixedBaudRate", fixedBaudRateBps);
  fixedBaudRateRegister = Device::bpsToBaudRegister(fixedBaudRateBps);
  document.query("SpeedUpdatePeriod", speedUpdatePeriod);
  document.query("CommandTimeout", commandTimeout);
  document.query("SerialDeviceNumber", serialDeviceNumber);
  document.query("CrcMode", crcMode, Singleton<CrcModes>::getInstance());
  document.query("OverTemp/Min", overTempMin);
  document.query("OverTemp/Max", overTempMax);
  document.query("InputMode", inputMode, Singleton<InputModes>::getInstance());
  document.query("PwmMode", pwmMode, Singleton<PwmModes>::getInstance());
  document.query("PwmPeriodFactor", pwmPeriodFactor);
  document.query("MixingMode", mixingMode,
    Singleton<MixingModes>::getInstance());
  document.query("PulsePeriod/Min", minPulsePeriod);
  document.query("PulsePeriod/Max", maxPulsePeriod);
  document.query("RcTimeout", rcTimeout);
  document.query("IgnorePotDisconnect", ignorePotDisconnect);
  document.query("TempLimitGradual", tempLimitGradual);
  document.query("ConsecGoodPulses", consecGoodPulses);
  document.query("MotorInvert", motorInvert);
  document.query("SpeedZeroBrakeAmount", speedZeroBrakeAmount);
  document.query("IgnoreErrLineHigh", ignoreErrLineHigh);
  document.query("VinMultiplierOffset", vinMultiplierOffset);
  document.query("LowVinShutoffTimeout", lowVinShutoffTimeout);
  document.query("LowVinShutoffMv", lowVinShutoffMv);
  document.query("LowVinStartupMv", lowVinStartupMv);
  document.query("HighVinShutoffMv", highVinShutoffMv);
  document.query("SerialMode", serialMode,
    Singleton<SerialModes>::getInstance());

  for (int i = 0; i < sizeof(inputChannels)/sizeof(InputChannel); ++i)
    if (document.hasSection(Singleton<Device::InputChannels>::getInstance()[
      (Device::InputChannel)i])) {
    const Pololu::Configuration::Section& section =
      document(Singleton<Device::InputChannels>::getInstance()[
      (Device::InputChannel)i]);

    section.query("Invert", inputChannels[i].invert);
    section.query("ScalingDegree", inputChannels[i].scalingDegree);
    section.query("AlternateUse", inputChannels[i].alternateUse,
      Singleton<InputChannel::AlternateUses>::getInstance());
    section.query("PinMode", inputChannels[i].pinMode,
      Singleton<InputChannel::PinModes>::getInstance());
    section.query("Error/Min", inputChannels[i].errorMin);
    section.query("Error/Max", inputChannels[i].errorMax);
    section.query("Input/Min", inputChannels[i].inputMin);
    section.query("Input/Max", inputChannels[i].inputMax);
    section.query("InputNeutral/Min", inputChannels[i].inputNeutralMin);
    section.query("InputNeutral/Max", inputChannels[i].inputNeutralMax);
  }

  for (int i = 0; i < sizeof(motorLimits)/sizeof(MotorLimits); ++i)
    if (document.hasSection(Singleton<Device::MotorLimits>::getInstance()[
      (Device::MotorLimit)i])) {
    const Pololu::Configuration::Section& section =
      document(Singleton<Device::MotorLimits>::getInstance()[
      (Device::MotorLimit)i]);

    section.query("MaxSpeed", motorLimits[i].maxSpeed);
    section.query("MaxAcceleration", motorLimits[i].maxAcceleration);
    section.query("MaxAcceleration", motorLimits[i].maxAcceleration);
    section.query("MaxDeceleration", motorLimits[i].maxDeceleration);
    size_t brakeDurationMs =
      Device::brakeRegisterToMs(motorLimits[i].brakeDuration);
    section.query("BrakeDuration", brakeDurationMs);
    motorLimits[i].brakeDuration = Device::msToBrakeRegister(brakeDurationMs);
    section.query("StartingSpeed", motorLimits[i].startingSpeed);
  }
}

void Pololu::Smc::Usb::Settings::write(std::ostream& stream) const {
  Pololu::Configuration::Document document("SmcSettings");

  document["NeverSuspend"] = neverSuspend;
  document["UartResponseDelay"] = uartResponseDelay;
  document["UseFixedBaudRate"] = useFixedBaudRate;
  document["DisableSafeStart"] = disableSafeStart;
  document["FixedBaudRate"] = Device::baudRegisterToBps(fixedBaudRateRegister);
  document["SpeedUpdatePeriod"] = speedUpdatePeriod;
  document["CommandTimeout"] = commandTimeout;
  document["SerialDeviceNumber"] = serialDeviceNumber;
  document["CrcMode"] = Singleton<CrcModes>::getInstance()[
    (CrcMode)crcMode];
  document["OverTemp/Min"] = overTempMin;
  document["OverTemp/Max"] = overTempMax;
  document["InputMode"] = Singleton<InputModes>::getInstance()[
    (InputMode)inputMode];
  document["PwmMode"] = Singleton<PwmModes>::getInstance()[(PwmMode)pwmMode];
  document["PwmPeriodFactor"] = pwmPeriodFactor;
  document["MixingMode"] = Singleton<MixingModes>::getInstance()[
    (MixingMode)mixingMode];
  document["PulsePeriod/Min"] = minPulsePeriod;
  document["PulsePeriod/Max"] = maxPulsePeriod;
  document["RcTimeout"] = rcTimeout;
  document["IgnorePotDisconnect"] = ignorePotDisconnect;
  document["TempLimitGradual"] = tempLimitGradual;
  document["ConsecGoodPulses"] = consecGoodPulses;
  document["MotorInvert"] = motorInvert;
  document["SpeedZeroBrakeAmount"] = speedZeroBrakeAmount;
  document["IgnoreErrLineHigh"] = ignoreErrLineHigh;
  document["VinMultiplierOffset"] = vinMultiplierOffset;
  document["LowVinShutoffTimeout"] = lowVinShutoffTimeout;
  document["LowVinShutoffMv"] = lowVinShutoffMv;
  document["LowVinStartupMv"] = lowVinStartupMv;
  document["HighVinShutoffMv"] = highVinShutoffMv;
  document["SerialMode"] = Singleton<SerialModes>::getInstance()[
    (SerialMode)serialMode];

  for (int i = 0; i < sizeof(inputChannels)/sizeof(InputChannel); ++i) {
    Pololu::Configuration::Section& section =
      document(Singleton<Device::InputChannels>::getInstance()[
      (Device::InputChannel)i]);

    section["Invert"] = inputChannels[i].invert;
    section["ScalingDegree"] = inputChannels[i].scalingDegree;
    section["AlternateUse"] =
      Singleton<InputChannel::AlternateUses>::getInstance()[
      (InputChannel::AlternateUse)inputChannels[i].alternateUse];
    section["PinMode"] = Singleton<InputChannel::PinModes>::getInstance()[
      (InputChannel::PinMode)inputChannels[i].pinMode];
    section["Error/Min"] = inputChannels[i].errorMin;
    section["Error/Max"] = inputChannels[i].errorMax;
    section["Input/Min"] = inputChannels[i].inputMin;
    section["Input/Max"] = inputChannels[i].inputMax;
    section["InputNeutral/Min"] = inputChannels[i].inputNeutralMin;
    section["InputNeutral/Max"] = inputChannels[i].inputNeutralMax;
  }

  for (int i = 0; i < sizeof(motorLimits)/sizeof(MotorLimits); ++i) {
    Pololu::Configuration::Section& section =
      document(Singleton<Device::MotorLimits>::getInstance()[
      (Device::MotorLimit)i]);

    section["MaxSpeed"] = motorLimits[i].maxSpeed;
    section["MaxAcceleration"] = motorLimits[i].maxAcceleration;
    section["MaxAcceleration"] = motorLimits[i].maxAcceleration;
    section["MaxDeceleration"] = motorLimits[i].maxDeceleration;
    section["BrakeDuration"] =
      Device::brakeRegisterToMs(motorLimits[i].brakeDuration);
    section["StartingSpeed"] = motorLimits[i].startingSpeed;
  }

  stream << document;
}

std::istream& operator>>(std::istream& stream,
    Pololu::Smc::Usb::Settings& settings) {
  settings.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Smc::Usb::Settings& settings) {
  settings.write(stream);
  return stream;
}
