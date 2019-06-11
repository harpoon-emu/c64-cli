#include "c64.hh"
#include "cpu/mos_6510.hh"
#include "memory/memory.hh"

#include "harpoon/clock/threaded_clock.hh"
#include "harpoon/execution/up_execution_unit.hh"

#include <chrono>

namespace commodore {

c64::c64(const harpoon::log::log_ptr& log)
	: harpoon::computer_system("Commodore 64") {
	set_log(log);
}

c64::~c64() {}

void c64::create() {
	create_memory();
	create_execution_unit();

	auto execution_unit = std::static_pointer_cast<harpoon::execution::up_execution_unit>(get_main_execution_unit());
	auto cpu = std::static_pointer_cast<cpu::mos_6510>(execution_unit->get_processing_unit());
	auto memory = std::static_pointer_cast<memory::memory>(get_main_memory());

	memory->add_memory(cpu->get_zero_page());
	cpu->set_memory(memory);
}

void c64::create_execution_unit() {
	auto execution_unit = harpoon::execution::make_up_execution_unit("Execution unit");
	set_main_execution_unit(execution_unit);

	auto clock
	    = harpoon::clock::make_threaded_clock<std::chrono::high_resolution_clock>(1000000, "Clock");
	execution_unit->set_clock(clock);

	auto cpu = std::make_shared<cpu::mos_6510>("MOS 6510");
	execution_unit->set_processing_unit(cpu);

	cpu->create();
}

void c64::create_memory() {
	auto main_memory = std::make_shared<memory::memory>("Memory", harpoon::memory::address_range{0, 0xffff});
	set_main_memory(main_memory);

	main_memory->create();
}

void c64::prepare() {
	harpoon::computer_system::prepare();
}

}
