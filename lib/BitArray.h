#pragma once
#include <iostream>

class BitArray
{
public:
    BitArray(int bit_size);
    BitArray(uint8_t *bitArray, int bitSize);
    ~BitArray();

    uint8_t GetBit(int i);
    uint8_t GetByte(int i);
    bool SetBit(int i, uint8_t value);
    bool AppendBit(uint8_t value);
    uint8_t PopBit();
    uint8_t *GetBitArray();
    void CountOperations();
    int GetOperations();
    int GetSize();
    int AlignIndex();

private:
    uint8_t *_bitArray;
	int size;
	int index;
    int opsCounter;

	uint8_t BITS[8] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};
};

