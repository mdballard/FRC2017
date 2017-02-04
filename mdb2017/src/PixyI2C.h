//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This file is for defining the link class for I2C communications.  
//
// Note, the PixyI2C class takes two optional arguments, the first being the I2C address 
// of the Pixy you want to talk to and the second being the port on the RoboRIO you want to use (Onboard or MXP).
// The default address and port are 0x54 and kOnboard respectively.
// So, for example, if you wished to talk to Pixy at I2C address 0x55 and using the MXP port, declare like this:
//
// PixyI2C *Pixy = new PixyI2C(0x55, I2C::Port::kMXP);
//

#ifndef _PIXYI2C_H
#define _PIXYI2C_H

#include "TPixy.h"

#define PIXY_I2C_DEFAULT_ADDR           0x54
#define PIXY_I2C_DEFAULT_PORT     I2C::Port::kOnboard

class LinkI2C
{
public:
  LinkI2C(uint8_t address=PIXY_I2C_DEFAULT_ADDR, I2C::Port port=PIXY_I2C_DEFAULT_PORT): Wire(port, address)
  {

  }
  uint16_t getWord()
  {

	Wire.ReadOnly(1,&byte1);
	Wire.ReadOnly(1,&byte2);

    uint16_t w = (byte2 << 8) + byte1;
    return w;
  }
  uint8_t getByte()
  {
	Wire.ReadOnly(1,&byte1);
	return byte1;
  }

  int8_t send(uint8_t *data, uint8_t len)
  {
    Wire.WriteBulk(data, len);
    return len;
  }
  
private:
  I2C Wire;
  uint16_t word;
  uint8_t  byte1, byte2;
};

typedef TPixy<LinkI2C> PixyI2C;

#endif
