#ifndef HARPOON_MEMORY_ADDRESS_RANGE_HH
#define HARPOON_MEMORY_ADDRESS_RANGE_HH

#include "harpoon/harpoon.hh"
#include "harpoon/memory/address.hh"

namespace harpoon {
namespace memory {

class address_range {
public:
	address_range(address start = {}, std::uint_fast64_t end = {}) 
		: _start(start), _end(end) {}
	address_range(const address_range&) = default;
	address_range& operator=(const address_range&) = default;

	bool operator==(const address_range& second) const {
		return get_start() == second.get_start() && get_end() == second.get_end();
	}

	address get_start() const {
		return _start;
	}

	void set_start(address start) {
		_start = start;
	}

	address get_end() const {
		return _end;
	}

	void set_end(address end) {
		_end = end;
	}

	std::uint_fast64_t get_length() const {
		return _end - _start + 1;
	}

	void set_length(std::uint_fast64_t length) {
		_end = _start + length - 1;
	}

	void set_range(address start, address end) {
		set_start(start);
		set_end(end);
	}

	void set_start_and_length(address start, std::uint_fast64_t length) {
		set_start(start);
		set_length(length);
	}

	bool has_address(address address) const {
		return address >= get_start() && address <= get_end();
	}

	bool overlaps(const address_range& second) const {
		return has_address(second.get_start()) || has_address(second.get_end());
	}

private:
	address _start{};
	address _end{};
};

}
}

#endif
