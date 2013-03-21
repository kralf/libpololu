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

#include <libusb.h>

#include "base/singleton.h"

#include "request.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usb::Request::TypeFlags::TypeFlags() {
  (*this)[typeStandard] = LIBUSB_REQUEST_TYPE_STANDARD;
  (*this)[typeClass] = LIBUSB_REQUEST_TYPE_CLASS;
  (*this)[typeVendor] = LIBUSB_REQUEST_TYPE_VENDOR;
  (*this)[typeReserved] = LIBUSB_REQUEST_TYPE_RESERVED;
}

Pololu::Usb::Request::RecipientFlags::RecipientFlags() {
  (*this)[recipientDevice] = LIBUSB_RECIPIENT_DEVICE;
  (*this)[recipientInterface] = LIBUSB_RECIPIENT_INTERFACE;
  (*this)[recipientEndpoint] = LIBUSB_RECIPIENT_ENDPOINT;
  (*this)[recipientOther] = LIBUSB_RECIPIENT_OTHER;
}

Pololu::Usb::Request::DirectionFlags::DirectionFlags() {
  (*this)[directionIn] = LIBUSB_ENDPOINT_IN;
  (*this)[directionOut] = LIBUSB_ENDPOINT_OUT;
}

Pololu::Usb::Request::Request(Type type, Recipient recipient, Direction
    direction, unsigned char request, unsigned short value, unsigned short
    index, const std::vector<unsigned char>& data) :
  type(type),
  recipient(recipient),
  direction(direction),
  request(request),
  value(value),
  index(index),
  data(data) {
}

Pololu::Usb::Request::Request(Type type, unsigned char request, unsigned
    short value, unsigned short index, size_t inputDataSize) :
  type(type),
  recipient(recipientDevice),
  direction(directionIn),
  request(request),
  value(value),
  index(index),
  data(inputDataSize) {
}

Pololu::Usb::Request::Request(Type type, unsigned char request, unsigned
    short value, unsigned short index, const std::vector<unsigned char>&
    outputData) :
  type(type),
  recipient(recipientDevice),
  direction(directionOut),
  request(request),
  value(value),
  index(index),
  data(outputData) {
}

Pololu::Usb::Request::Request(const Request& src) :
  type(src.type),
  recipient(src.recipient),
  direction(src.direction),
  request(src.request),
  value(src.value),
  index(src.index),
  data(src.data) {
}

Pololu::Usb::Request::~Request() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Pololu::Usb::Request::Type Pololu::Usb::Request::getType() const {
  return type;
}

void Pololu::Usb::Request::setType(Type type) {
  this->type = type;
}

Pololu::Usb::Request::Recipient Pololu::Usb::Request::getRecipient() const {
  return recipient;
}

void Pololu::Usb::Request::setRecipient(Recipient recipient) {
  this->recipient = recipient;
}

Pololu::Usb::Request::Direction Pololu::Usb::Request::getDirection() const {
  return direction;
}

void Pololu::Usb::Request::setDirection(Direction direction) {
  this->direction = direction;
}

unsigned char Pololu::Usb::Request::getRequestType() const {
  return Singleton<TypeFlags>::getInstance()[type] |
    Singleton<RecipientFlags>::getInstance()[recipient] |
    Singleton<DirectionFlags>::getInstance()[direction];
}

unsigned char Pololu::Usb::Request::getRequest() const {
  return request;
}

void Pololu::Usb::Request::setRequest(unsigned char request) {
  this->request = request;
}

unsigned short Pololu::Usb::Request::getValue() const {
  return value;
}

void Pololu::Usb::Request::setValue(unsigned short value) {
  this->value = value;
}

unsigned short Pololu::Usb::Request::getIndex() const {
  return index;
}

void Pololu::Usb::Request::setIndex(unsigned short index) {
  this->index = index;
}

const std::vector<unsigned char>& Pololu::Usb::Request::getData() const {
  return data;
}

void Pololu::Usb::Request::setData(const std::vector<unsigned char>& data) {
  this->data = data;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usb::Request& Pololu::Usb::Request::operator=(const Request& src) {
  type = src.type;
  recipient = src.recipient;
  direction = src.direction;

  request = src.request;
  value = src.value;
  index = src.index;

  data = src.data;

  return *this;
}
