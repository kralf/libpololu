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

#include "variables.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Smc::Usb::Variables::Errors::Errors() {
  (*this)[errorNone] = "None";
  (*this)[errorSafeStart] = "SafeStart";
  (*this)[errorChannelInvalid] = "ChannelInvalid";
  (*this)[errorSerial] = "Serial";
  (*this)[errorCommandTimeout] = "CommandTimeout";
  (*this)[errorLimitSwitch] = "LimitSwitch";
  (*this)[errorVinLow] = "VinLow";
  (*this)[errorVinHigh] = "VinHigh";
  (*this)[errorTemperatureHigh] = "TemperatureHigh";
  (*this)[errorMotorDriver] = "MotorDriver";
  (*this)[errorLineHigh] = "LineHigh";
}

Pololu::Smc::Usb::Variables::SerialErrors::SerialErrors() {
  (*this)[serialErrorNone] = "None";
  (*this)[serialErrorParity] = "Parity";
  (*this)[serialErrorFrame] = "Frame";
  (*this)[serialErrorNoise] = "Noise";
  (*this)[serialErrorRxOverrun] = "RxOverrun";
  (*this)[serialErrorFormat] = "Format";
  (*this)[serialErrorCrc] = "Crc";
}

Pololu::Smc::Usb::Variables::LimitStatuses::LimitStatuses() {
  (*this)[limitStatusNone] = "None";
  (*this)[limitStatusStartedState] = "StartedState";
  (*this)[limitStatusTemperature] = "Temperature";
  (*this)[limitStatusMaxSpeed] = "MaxSpeed";
  (*this)[limitStatusStartingSpeed] = "StartingSpeed";
  (*this)[limitStatusAcceleration] = "Acceleration";
  (*this)[limitStatusRc1] = "Rc1";
  (*this)[limitStatusRc2] = "Rc2";
  (*this)[limitStatusAnalog1] = "Analog1";
  (*this)[limitStatusAnalog2] = "Analog2";
  (*this)[limitStatusUsbKill] = "UsbKill";
}

Pololu::Smc::Usb::Variables::InputChannel::InputChannel() :
  unlimitedRawValue(0),
  rawValue(0),
  scaledValue(0),
  reserved0(0) {
}

Pololu::Smc::Usb::Variables::MotorLimits::MotorLimits() :
  maxSpeed(0),
  maxAcceleration(0),
  maxDeceleration(0),
  brakeDuration(0),
  startingSpeed(0),
  reserved0(0) {
}

Pololu::Smc::Usb::Variables::Variables() :
  errorStatus(errorNone),
  errorOccurred(errorNone),
  serialErrorOccurred(serialErrorNone),
  limitStatus(limitStatusNone),
  targetSpeed(0),
  speed(0),
  brakeAmount(0),
  vinMv(0),
  temperature(0),
  reserved0(0),
  rcPeriod(0),
  baudRateRegister(0),
  timeMs(0) {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Pololu::Smc::Usb::Variables::write(std::ostream& stream) const {
  Pololu::Configuration::Document document("SmcVariables");

  for (int i = 0; i <= 9; ++i)
    document["ErrorStatus/"+Singleton<Errors>::getInstance()[
      (Error)(1 << i)]] = (bool)(errorStatus & (1 << i));
  for (int i = 0; i <= 9; ++i)
    document["ErrorOccurred/"+Singleton<Errors>::getInstance()[
      (Error)(1 << i)]] = (bool)(errorOccurred & (1 << i));
  for (int i = 0; i <= 6; ++i)
    document["SerialErrorOccurred/"+Singleton<SerialErrors>::getInstance()[
      (SerialError)(1 << i)]] = (bool)(serialErrorOccurred & (1 << i));
  for (int i = 0; i <= 9; ++i)
    document["LimitStatus/"+Singleton<LimitStatuses>::getInstance()[
      (LimitStatus)(1 << i)]] = (bool)(limitStatus & (1 << i));
  document["TargetSpeed"] = targetSpeed;
  document["Speed"] = speed;
  document["BrakeAmount"] = brakeAmount;
  document["VinMv"] = vinMv;
  document["Temperature"] = Device::temperatureRegisterToDeg(temperature);
  document["RcPeriod"] = rcPeriod;
  document["BaudRate"] = Device::baudRegisterToBps(baudRateRegister);
  document["TimeMs"] = timeMs;

  for (int i = 0; i < sizeof(inputChannels)/sizeof(InputChannel); ++i) {
    Pololu::Configuration::Section& section =
      document(Singleton<Device::InputChannels>::getInstance()[
      (Device::InputChannel)i]);

    section["UnlimitedRawValue"] = inputChannels[i].unlimitedRawValue;
    section["RawValue"] = inputChannels[i].rawValue;
    section["ScaledValue"] = inputChannels[i].scaledValue;
  }

  for (int i = 0; i < sizeof(motorLimits)/sizeof(MotorLimits); ++i) {
    Pololu::Configuration::Section& section =
      document(Singleton<Device::MotorLimits>::getInstance()[
      (Device::MotorLimit)i]);

    section["MaxSpeed"] = motorLimits[i].maxSpeed;
    section["MaxAcceleration"] = motorLimits[i].maxAcceleration;
    section["MaxDeceleration"] = motorLimits[i].maxDeceleration;
    section["BrakeDuration"] =
      Device::brakeRegisterToMs(motorLimits[i].brakeDuration);
    section["StartingSpeed"] = motorLimits[i].startingSpeed;
  }

  document.write(stream);
}

std::ostream& operator<<(std::ostream& stream, const
    Pololu::Smc::Usb::Variables& variables) {
  variables.write(stream);
  return stream;
}
