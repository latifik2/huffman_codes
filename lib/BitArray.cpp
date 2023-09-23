#include "BitArray.h"
#include <cstring>

BitArray::BitArray(int bit_size)
	: index(0), size(bit_size / 8), opsCounter(0) {
    // this->index = 0;
	// this->size = bit_size / 8;
	if (bit_size % 8 != 0)
		this->size++;
		
	bit_array = new uint8_t[this->size];
	std::fill(&bit_array[0], &bit_array[this->size - 1], 0);
}

BitArray::BitArray(uint8_t *bit_array, int bit_size)
	: index(0), size(bit_size / 8), opsCounter(0) {
    // this->index = 0;
	// this->size = bit_size / 8;
	if (bit_size % 8 != 0)
		this->size++;
		
	bit_array = new uint8_t[this->size];
    std::memcpy(this->bit_array, bit_array, this->size);
}

BitArray::~BitArray() {
	//delete[] bit_array;
}

uint8_t BitArray::GetBit(int i) {
	int byte_index = i / 8;
	if (byte_index >= this->size)
		return 2;

	//int bit_index = i < 7 ? i % 8 : 7 - (i % 8);
	int bit_index = 7 - (i % 8);

	return bit_array[byte_index] & BITS[bit_index] > 0 ? 1 : 0;
}

uint8_t BitArray::GetByte(int i) {
	if (i >= this->size)
		return 0;
		
	return bit_array[i];
}

bool BitArray::SetBit(int i, uint8_t value) {
	int byte_index = i / 8;
	if (byte_index >= this->size)
		return false;

	// int bit_index = i < 7 ? i % 8 : 7 - (i % 8);
	int bit_index = 7 - (i % 8);
		//bit_array[byte_index] |= value == 1 ? BITS[bit_index] : ~BITS[bit_index];
	if (value == 1)
		bit_array[byte_index] |= BITS[bit_index];
	else
		bit_array[byte_index] &= ~BITS[bit_index];

	return true;
}

bool BitArray::AppendBit(uint8_t value) {
	bool result = SetBit(this->index, value);
	if (result)
		this->index++;
	
	return result;
}

uint8_t BitArray::PopBit() {
    uint8_t result = BitArray::GetBit(this->index);
	if (result != 2)
		this->index++;
	return result;
}

uint8_t* BitArray::GetBitArray() {
	return this->bit_array;
}

void BitArray::CountOperations() {
	opsCounter++;
}

int BitArray::GetOperations() {
	return opsCounter;
}

int BitArray::GetSize() {
	return size;
}

int BitArray::AlignIndex() {
	int rest = index % 8;

	if (rest == 0)
		return index;
	
	index += index + (rest - 8);
	return index;
}