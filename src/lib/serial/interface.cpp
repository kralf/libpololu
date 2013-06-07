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

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "base/singleton.h"

#include "interface.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Serial::Interface::BaudRateError::BaudRateError(size_t baudRate) :
  Exception("Invalid baud rate: %d", baudRate) {
}

Pololu::Serial::Interface::DataBitsError::DataBitsError(unsigned char
    dataBits) :
  Exception("Invalid number of data bits: %d", dataBits) {
}

Pololu::Serial::Interface::StopBitsError::StopBitsError(unsigned char
    stopBits) :
  Exception("Invalid number of stop bits: %d", stopBits) {
}

Pololu::Serial::Interface::OpenError::OpenError(const std::string& address) :
  Exception("Error opening serial interface: %s", address.c_str()) {
}

Pololu::Serial::Interface::SetupError::SetupError(const std::string&
    address) :
  Exception("Error setting serial interface attributes: %s", address.c_str()) {
}

Pololu::Serial::Interface::SendError::SendError(const std::string& address) :
  Exception("Send failed on serial interface: %s", address.c_str()) {
}

Pololu::Serial::Interface::ReceiveTimeout::ReceiveTimeout(const std::string&
    address) :
  Exception("Receive timeout on serial interface: %s", address.c_str()) {
}

Pololu::Serial::Interface::ReceiveError::ReceiveError(const std::string&
    address) :
  Exception("Receive failed on serial interface: %s", address.c_str()) {
}

Pololu::Serial::Interface::BaudRateFlags::BaudRateFlags() {
  (*this)[50] = B50;
  (*this)[75] = B75;
  (*this)[110] = B110;
  (*this)[134] = B134;
  (*this)[150] = B150;
  (*this)[200] = B200;
  (*this)[300] = B300;
  (*this)[600] = B600;
  (*this)[1200] = B1200;
  (*this)[1800] = B1800;
  (*this)[2400] = B2400;
  (*this)[4800] = B4800;
  (*this)[9600] = B9600;
  (*this)[19200] = B19200;
  (*this)[38400] = B38400;
  (*this)[57600] = B57600;
  (*this)[115200] = B115200;
  (*this)[230400] = B230400;
}

Pololu::Serial::Interface::DataBitsFlags::DataBitsFlags() {
  (*this)[5] = CS5;
  (*this)[6] = CS6;
  (*this)[7] = CS7;
  (*this)[8] = CS8;
}

Pololu::Serial::Interface::StopBitsFlags::StopBitsFlags() {
  (*this)[1] = 0;
  (*this)[2] = CSTOPB;
}

Pololu::Serial::Interface::ParityFlags::ParityFlags() {
  (*this)[parityNone] = 0;
  (*this)[parityOdd] = PARENB | PARODD;
  (*this)[parityEven] = PARENB;
}

Pololu::Serial::Interface::Interface(const std::string& address, size_t
    baudRate, unsigned char dataBits, unsigned char stopBits, Parity parity) :
  Pololu::Interface(address),
  baudRate(baudRate),
  dataBits(dataBits),
  stopBits(stopBits),
  parity(parity),
  handle(0) {
}

Pololu::Serial::Interface::Interface(const Interface& src) :
  Pololu::Interface(src),
  baudRate(src.baudRate),
  dataBits(src.dataBits),
  stopBits(src.stopBits),
  parity(src.parity),
  handle(0) {
}

Pololu::Serial::Interface::~Interface() {
  if (handle)
    close();
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned int Pololu::Serial::Interface::BaudRateFlags::operator[](
    size_t baudRate) const {
  const_iterator it = find(baudRate);
  if (it != end())
    return it->second;
  else
    throw BaudRateError(baudRate);
}

unsigned int Pololu::Serial::Interface::DataBitsFlags::operator[](
    unsigned char dataBits) const {
  const_iterator it = find(dataBits);
  if (it != end())
    return it->second;
  else
    throw DataBitsError(dataBits);
}

unsigned int Pololu::Serial::Interface::StopBitsFlags::operator[](
    unsigned char stopBits) const {
  const_iterator it = find(stopBits);
  if (it != end())
    return it->second;
  else
    throw StopBitsError(stopBits);
}

size_t Pololu::Serial::Interface::getBaudRate() const {
  return baudRate;
}

void Pololu::Serial::Interface::setBaudRate(size_t baudRate) {
  this->baudRate = baudRate;

  if (isOpen())
    setup();
}

unsigned char Pololu::Serial::Interface::getDataBits() const {
  return dataBits;
}

void Pololu::Serial::Interface::setDataBits(unsigned char dataBits) {
  this->dataBits = dataBits;

  if (isOpen())
    setup();
}

unsigned char Pololu::Serial::Interface::getStopBits() const {
  return stopBits;
}

void Pololu::Serial::Interface::setStopBits(unsigned char stopBits) {
  this->stopBits = stopBits;

  if (isOpen())
    setup();
}

Pololu::Serial::Interface::Parity Pololu::Serial::Interface::getParity()
    const {
  return parity;
}

void Pololu::Serial::Interface::setParity(Parity parity) {
}

std::string Pololu::Serial::Interface::getName() const {
  return "Serial (TTL/USB) Interface";
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Serial::Interface& Pololu::Serial::Interface::operator=(const
    Interface& src) {
  if (handle)
    close();

  baudRate = src.baudRate;
  dataBits = src.dataBits;
  stopBits = src.stopBits;
  parity = src.parity;

  Pololu::Interface::operator=(src);

  return *this;
}

void Pololu::Serial::Interface::open() {
  if (!handle) {
    handle = ::open(address.c_str(), O_RDWR | O_NDELAY);

    if (handle > 0)
      setup();
    else
      throw OpenError(address);
  }
}

void Pololu::Serial::Interface::close() {
  if (handle) {
    tcdrain(handle);
    tcflush(handle, TCIOFLUSH);
    ::close(handle);

    handle = 0;
  }
}

Pololu::Pointer<Pololu::Device> Pololu::Serial::Interface::discoverDevice()
    const {
  return 0;
}

void Pololu::Serial::Interface::send(const std::vector<unsigned char>&
    data) {
  if (handle) {
    int i = 0;

    while (i < data.size()) {
      ssize_t result;
      while ((result = ::write(handle, &data[i], data.size()-i)) == 0);

      if ((result < 0) && (errno != EWOULDBLOCK))
        throw SendError(address);
      else if (result > 0)
        i += result;
    }
  }
  else
    throw OperationError();
}

void Pololu::Serial::Interface::receive(std::vector<unsigned char>& data) {
  if (handle) {
    size_t i = 0;
    struct timeval time;
    fd_set set;
    int error;

    while (i < data.size()) {
      time.tv_sec = 0;
      time.tv_usec = timeout*1e6;

      FD_ZERO(&set);
      FD_SET(handle, &set);

      error = select(handle+1, &set, NULL, NULL, &time);
      if (error == 0)
        throw ReceiveTimeout(address);
      else if (error < 0)
        throw ReceiveError(address);

      ssize_t result;
      result = ::read(handle, &data[i], data.size()-i);

      if ((result < 0) && (result != EWOULDBLOCK))
        throw ReceiveError(address);
      else if (result > 0)
        i += result;
    }
  }
  else
    throw OperationError();
}

void Pololu::Serial::Interface::transfer(Request& request) {
}

void Pololu::Serial::Interface::transfer(Pololu::Request& request) {
  Request* serialRequest = dynamic_cast<Request*>(&request);

  if (serialRequest)
    transfer(*serialRequest);
  else
    throw RequestError();
}

bool Pololu::Serial::Interface::isOpen() const {
  return handle;
}

void Pololu::Serial::Interface::setup() {
  struct termios settings;
  memset(&settings, 0, sizeof(settings));

  settings.c_cflag |= Singleton<BaudRateFlags>::getInstance()[baudRate];
  settings.c_cflag |= Singleton<DataBitsFlags>::getInstance()[dataBits];
  settings.c_cflag |= Singleton<StopBitsFlags>::getInstance()[stopBits];
  settings.c_cflag |= Singleton<ParityFlags>::getInstance()[parity];

  settings.c_cflag |= CLOCAL;
  settings.c_iflag = IGNPAR;

  tcflush(handle, TCIOFLUSH);
  if (tcsetattr(handle, TCSANOW, &settings) < 0)
    throw SetupError(address);
}
