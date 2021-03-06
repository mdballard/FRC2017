/*
 * Pixy.h
 *
 *  Created on: Feb 4, 2017
 *      Author: mdbal
 */

#ifndef SRC_PIXY_H_
#define SRC_PIXY_H_

#include "WPILIB.h"
#include "I2C.h"
#include "SensorBase.h"
#include <vector>


// Communication/misc parameters
#define PIXY_INITIAL_ARRAYSIZE      130
#define PIXY_MAXIMUM_ARRAYSIZE      130
#define PIXY_START_WORD             0xaa55
#define PIXY_START_WORD_CC          0xaa56
#define PIXY_START_WORDX            0x55aa
#define PIXY_MAX_SIGNATURE          7
#define PIXY_DEFAULT_ARGVAL         0xffff

// Pixy x-y position values
#define PIXY_MIN_X                  0L
#define PIXY_CENT_X                 160L
#define PIXY_MAX_X                  319L
#define PIXY_MIN_Y                  0L
#define PIXY_CENT_Y                 100L
#define PIXY_MAX_Y                  199L

// RC-servo values
#define PIXY_RCS_MIN_POS            0L
#define PIXY_RCS_MAX_POS            1000L
#define PIXY_RCS_CENTER_POS         ((PIXY_RCS_MAX_POS-PIXY_RCS_MIN_POS)/2)

#define PIXY_I2C_DEFAULT_ADDR     0x54
#define PIXY_I2C_DEFAULT_PORT     I2C::Port::kOnboard

/*
 * I2C Object Block
 * Bytes    16-bit word    Description
----------------------------------------------------------------
	0, 1     y              sync: 0xaa55=normal object, 0xaa56=color code object
	2, 3     y              checksum (sum of all 16-bit words 2-6, that is, bytes 4-13)
	4, 5     y              signature number
	6, 7     y              x center of object
	8, 9     y              y center of object
	10, 11   y              width of object
	12, 13   y              height of object
 */

/*
 * I2C Servo Control
 * Bytes    16-bit word   Description
----------------------------------------------------------------
	0, 1     y             servo sync (0xff00)
	2, 3     y             servo 0 (pan) position, between 0 and 1000
	4, 5     y             servo 1 (tilt) position, between 0 and 1000
 */

/*
 * I2C Camera Brightness
 * Bytes    16-bit word   Description
----------------------------------------------------------------
	0, 1     y             camera brightness sync (0xfe00)
	2        n             brightness value
 */

/*
 * I2C LED Control
 * Bytes    16-bit word   Description
----------------------------------------------------------------
	0, 1     y             LED sync (0xfd00)
	2        n             red value
	3        n             green value
	4        n             blue value
 */

enum BlockType
{
  NORMAL_BLOCK,
  CC_BLOCK,
  UNDEFINED
};

struct Block
{
  uint16_t signature;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t angle;
  float    aspectRatio;
  uint16_t x_top;
  uint16_t x_bottom;
  uint16_t y_left;
  uint16_t y_right;
  uint16_t x_deviation;
  uint16_t y_deviation;
  void print();
};


class Pixy {
public:
	Pixy(uint8_t address, I2C::Port port=PIXY_I2C_DEFAULT_PORT);
	~Pixy();

	void      Set_AlignmentOffset(int x, int y);
	uint16_t  GetBlocks(uint16_t maxBlocks=1000);
	int8_t    SetServos(uint16_t s0, uint16_t s1);
	int8_t    SetBrightness(uint8_t brightness);
	int8_t    SetLED(uint8_t r, uint8_t g, uint8_t b);
	std::vector<Block> signatures;

private:
	bool      GetStart();
	void      Resize();

	uint16_t  GetWord();
	uint8_t   GetByte();
	int8_t    Send(uint8_t *data, uint8_t len);

	bool      skipStart;
	BlockType blockType;
	uint16_t  blockCount;

	I2C::Port _port;
	uint8_t   _address;
	I2C       Wire;
	uint16_t  word;
	uint8_t   byte1, byte2;

	int       x_offset;
	int       y_offset;
};

#endif /* SRC_PIXY_H_ */
