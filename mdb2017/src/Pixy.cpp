/*
 * Pixy.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: mdbal
 */

#include <Pixy.h>
#include "Timer.h"

Pixy::Pixy(uint8_t address, enum frc::I2C::Port port) : Wire(port, address)
{
	_address = address;
	_port = port;

	skipStart = false;
	blockCount = 0;
	blockArraySize = PIXY_INITIAL_ARRAYSIZE;
	blocks = (Block *)malloc(sizeof(Block)*blockArraySize);
	byte1 = 0;
	byte2 = 0;
	word = 0;
	blockType = UNDEFINED;
	x_offset = 0;
	y_offset = 0;
}

Pixy::~Pixy()
{
	free(blocks);
}

void Pixy::Set_AlignmentOffset(int x, int y)
{
	x_offset = x;
	y_offset = y;
}


uint16_t Pixy::GetWord()
{

	Wire.ReadOnly(1,&byte1);
	Wire.ReadOnly(1,&byte2);

    uint16_t w = (byte2 << 8) + byte1;
    return w;
}

uint8_t Pixy::GetByte()
{
	Wire.ReadOnly(1,&byte1);
	return byte1;
}

int8_t Pixy::Send(uint8_t *data, uint8_t len)
{
    Wire.WriteBulk(data, len);
    return len;
}

bool Pixy::GetStart()
{
    uint16_t w, lastw;

    lastw = 0xffff;

    while(true)
    {
        w = GetWord();
        if (w==0 && lastw==0)
        {
            frc::Timer *delay = new frc::Timer();
            delay->Start();
            while (!delay->HasPeriodPassed(0.00005))
            {
                // Wait 50 microseconds
            }

            return false;
        } else if (w==PIXY_START_WORD && lastw==PIXY_START_WORD)
        {
             blockType = NORMAL_BLOCK;
             return true;
        } else if (w==PIXY_START_WORD_CC && lastw==PIXY_START_WORD)
        {
            blockType = CC_BLOCK;
            return true;
        } else if (w==PIXY_START_WORDX)
        {
            printf("reorder");
            GetByte(); // resync
        }
        lastw = w;
    }
}

void Pixy::Resize()
{
     blockArraySize += PIXY_INITIAL_ARRAYSIZE;
     blocks = (Block *)realloc(blocks, sizeof(Block)*blockArraySize);
}

uint16_t Pixy::GetBlocks(uint16_t maxBlocks)
{
     uint8_t i;
     uint16_t w, checksum, sum;
     Block *block;

     if (!skipStart)
     {
          if (GetStart()==false)
          return 0;
     } else
     {
          skipStart = false;
     }

     for(int blockCount=0; blockCount<maxBlocks && blockCount<PIXY_MAXIMUM_ARRAYSIZE;)
     {
          checksum = GetWord();
          if (checksum==PIXY_START_WORD) // we've reached the beginning of the next frame
          {
              skipStart = true;
              blockType = NORMAL_BLOCK;
              return blockCount;
          } else if (checksum==PIXY_START_WORD_CC)
          {
              skipStart = true;
              blockType = CC_BLOCK;
              return blockCount;
          } else if (checksum==0)
          {
              return blockCount;
          }

          if (blockCount>blockArraySize) Resize();

          block = blocks + blockCount;

          for (int i=0, sum=0; i<sizeof(Block)/sizeof(uint16_t); i++)
          {
              if (blockType==NORMAL_BLOCK && i>=5) // skip
              {
                   block->angle = 0;
                   break;
              }
              w = GetWord();
              sum += w;
              *((uint16_t *)block + i) = w;
          }

          if (checksum==sum)
          {
        	  blockCount++;
          } else
          {
              printf("cs error");
          }

          w = GetWord();
          if (w==PIXY_START_WORD)
          {
              blockType = NORMAL_BLOCK;
          } else if (w==PIXY_START_WORD_CC)
          {
              blockType = CC_BLOCK;
          } else
          {
              return blockCount;
          }
     }
     return 0;
}

int8_t Pixy::SetServos(uint16_t s0, uint16_t s1)
{
     uint8_t outBuf[6];

     outBuf[0] = 0x00;
     outBuf[1] = 0xff;
     *(uint16_t *)(outBuf + 2) = s0;
     *(uint16_t *)(outBuf + 4) = s1;

     return Send(outBuf, 6);
}

int8_t Pixy::SetBrightness(uint8_t brightness)
{
     uint8_t outBuf[3];

     outBuf[0] = 0x00;
     outBuf[1] = 0xfe;
     outBuf[2] = brightness;

     return Send(outBuf, 3);
}

int8_t Pixy::SetLED(uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t outBuf[5];

    outBuf[0] = 0x00;
    outBuf[1] = 0xfd;
    outBuf[2] = r;
    outBuf[3] = g;
    outBuf[4] = b;

    return Send(outBuf, 5);
}

