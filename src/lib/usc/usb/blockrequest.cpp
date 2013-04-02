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

#include "blockrequest.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Pololu::Usc::Usb::BlockRequest::BlockRequest(Type type, unsigned char request,
    unsigned short value, unsigned short startIndex, size_t inputDataSize,
    size_t blockSize) :
  Pololu::Usb::Request(type, request, value, startIndex, inputDataSize),
  blockSize(blockSize) {
  std::fill(data.begin(), data.end(), 0xFF);
}

Pololu::Usc::Usb::BlockRequest::BlockRequest(Type type, unsigned char
    request, unsigned short value, unsigned short startIndex, const
    std::vector<unsigned char>& outputData, size_t blockSize) :
  Pololu::Usb::Request(type, request, value, startIndex, outputData),
  blockSize(blockSize) {
}

Pololu::Usc::Usb::BlockRequest::BlockRequest(const BlockRequest& src) :
  Pololu::Usb::Request(src),
  blockSize(src.blockSize) {
}

Pololu::Usc::Usb::BlockRequest::~BlockRequest() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

size_t Pololu::Usc::Usb::BlockRequest::getBlockSize() const {
  return blockSize;
}

void Pololu::Usc::Usb::BlockRequest::setBlockSize(size_t blockSize) {
  this->blockSize = blockSize;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Pololu::Usc::Usb::BlockRequest& Pololu::Usc::Usb::BlockRequest::operator=(
    const BlockRequest& src) {
  Pololu::Usb::Request::operator=(src);
  blockSize = src.blockSize;

  return *this;
}

void Pololu::Usc::Usb::BlockRequest::transfer(libusb_device_handle* handle,
    std::vector<unsigned char>& data, double timeout) {
  for (unsigned short index = 0; index < (data.size()+blockSize-1)/blockSize;
      ++index) {
    std::vector<unsigned char> block(blockSize, 0xFF);

    for (int i = 0; i < blockSize; ++i)
      if (index*blockSize+i < data.size())
        block[i] = data[index*blockSize+i];

    Pololu::Usb::Request::transfer(handle, getRequestType(), request, 0,
      this->index+index, block, timeout);
  }
}
