#pragma once
#include <iostream>

class BitArray
{
public:
    BitArray(int bit_size);
    BitArray(uint8_t *bit_array, int bit_size);
    ~BitArray();

    uint8_t get_bit(int i);
    uint8_t get_byte(int i);
    bool set_bit(int i, uint8_t value);
    bool append_bit(uint8_t value);
    uint8_t pop_bit();
    const uint8_t *get_bit_array();

private:
    uint8_t *bit_array;
	int size;
	int index;

	uint8_t BITS[8] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};
};

