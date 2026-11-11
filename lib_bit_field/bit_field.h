// Copyright 2026 Khaferl Pavel

#ifndef LIB_BIT_FIELD_BIT_FIELD_H_
#define LIB_BIT_FIELD_BIT_FIELD_H_

#include <cstddef>
#include <iostream>
#include <stdexcept>

class BitField {
private:
	unsigned int* data;
	size_t size;

public:
	BitField();
	explicit BitField(size_t);
	BitField(const BitField&);
	~BitField();

	size_t get_size() const noexcept;
	void set_bit(size_t);
	void reset_bit(size_t);
	size_t get_index(size_t);
	// bool get_bit(size_t);

	BitField& operator=(const BitField&);
	BitField operator|(BitField) noexcept;
	BitField operator&(BitField) noexcept;
	BitField operator~() const;

	friend std::ostream& operator<<(std::ostream&, const BitField&);
	friend std::istream& operator>>(std::istream&, BitField&);
};

#endif  // LIB_BIT_FIELD_BIT_FIELD_H_