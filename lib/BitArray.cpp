#include "BitArray.h"
#include "../headers/Debug.h"
#include <cstring>

BitArray::BitArray(int bitSize)
	: index(0), size(bitSize / 8), opsCounter(0) {
    // this->index = 0;
	// this->size = bitSize / 8;
	if (bitSize % 8 != 0)
		this->size++;
		
	_bitArray = new uint8_t[this->size];
	std::fill(&_bitArray[0], &_bitArray[this->size - 1], 0);
}

BitArray::BitArray(uint8_t *bitArray, int bitSize)
	: index(0), size(bitSize / 8), opsCounter(0) {
    // this->index = 0;
	// this->size = bitSize / 8;
	if (bitSize % 8 != 0)
		this->size++;
		
	this->_bitArray = new uint8_t[this->size];
    std::memcpy(this->_bitArray, bitArray, this->size);
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
	//Debug::DebugPrint((int)_bitArray[byte_index]);
	//Debug::DebugPrint((int)BITS[bit_index]);


	return (uint8_t)(_bitArray[byte_index] & BITS[bit_index]) > 0 ? 1 : 0;
}

uint8_t BitArray::GetByte(int i) {
	if (i >= this->size)
		return 0;
		
	return _bitArray[i];
}

bool BitArray::SetBit(int i, BitState state) {
	int byte_index = i / 8;
	if (byte_index >= this->size)
		return false;

	// int bit_index = i < 7 ? i % 8 : 7 - (i % 8);
	int bitIndex = 7 - (i % 8);
		//bit_array[byte_index] |= value == 1 ? BITS[bit_index] : ~BITS[bit_index];
	
	switch (state)
	{
	case ON:
		_bitArray[byte_index] |= BITS[bitIndex];
		break;
	
	case OFF:
		_bitArray[byte_index] &= ~BITS[bitIndex];
		break;
	
	default:
		Debug::DebugPrint("Error! Unknown state!");
		return false;
		break;
	}

	return true;
}

bool BitArray::AppendBit(BitState state) {
	bool result = SetBit(this->index, state);
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
	return this->_bitArray;
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