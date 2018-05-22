#include <write.h>
#include <stdint.h>

void SysCallDispatcher(uint64_t id, uint64_t p1, uint64_t p2, uint64_t p3) {
	switch (id) {
		case 3:
			read_handler(p1, p2, p3);
			break;
		case 4:
			write_handler(p1, (char*)p2, (int)p3);
			break;
	}
	return;
}
