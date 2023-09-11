#include <iostream>


class BitArray {
private:
	uint8_t *bit_array;
	int size;
	int index;

	uint8_t BITS[8] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};

public:
	BitArray(int bit_size) {
		this->index = 0;
		this->size = bit_size / 8;
		if (bit_size % 8 != 0)
			this->size++;
		
		bit_array = new uint8_t[this->size];
		std::fill(&bit_array[0], &bit_array[this->size - 1], 0);
	}

	~BitArray() {
		delete[] bit_array;
	}


	uint8_t get_bit(int i) {
		int byte_index = i / 8;
		if (byte_index >= this->size)
			return 2;

		int bit_index = i < 7 ? i % 8 : 7 - (i % 8);

		return bit_array[byte_index] & BITS[bit_index] > 0 ? 1 : 0;
	}

	uint8_t get_byte(int i) {
		if (i >= this->size)
			return 0;
		
		return bit_array[i];
	}

	bool set_bit(int i, uint8_t value) {
		int byte_index = i / 8;
		if (byte_index >= this->size)
			return false;

		int bit_index = i < 7 ? i % 8 : 7 - (i % 8);
		//bit_array[byte_index] |= value == 1 ? BITS[bit_index] : ~BITS[bit_index];
		if (value == 1)
			bit_array[byte_index] |= BITS[bit_index];
		else
			bit_array[byte_index] &= ~BITS[bit_index];

		return true;
	}

	bool append_bit(uint8_t value) {
		bool result = set_bit(this->index, value);
		if (result)
			this->index++;
		
		return result;
	}

	const uint8_t *get_bit_array() {
		return bit_array;
	}	
};


int main() {

	BitArray ba(10);
	
	ba.set_bit(2, 1);
	ba.set_bit(9, 1);
	//ba.set_bit(9, 0);
	std::cout << (int)ba.get_byte(1) << '\n';

	
	return 0;
} 
