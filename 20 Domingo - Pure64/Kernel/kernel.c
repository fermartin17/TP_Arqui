#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>
#include <stdint.h>


extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	print("[x64BareBones]");
	newLine();

	print("CPU Vendor:");
	print(cpuVendor(buffer));
	newLine();

	print("[Loading modules]");
	newLine();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	print("[Done]");
	newLine();
	newLine();

	print("[Initializing kernel's binary]");
	newLine();

	clearBSS(&bss, &endOfKernel - &bss);

	print("  text: 0x");
	printHex((uint64_t)&text);
	newLine();
	print("  rodata: 0x");
	printHex((uint64_t)&rodata);
	newLine();
	print("  data: 0x");
	printHex((uint64_t)&data);
	newLine();
	print("  bss: 0x");
	printHex((uint64_t)&bss);

	newLine();
	print("[Done]");
	newLine();
	newLine();
	return getStackBase();
}
struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

struct vbe_mode_info_structure* screenData = 0x5C00;

static void fillrect(uint32_t donde,unsigned char r, unsigned char g, unsigned   char b, unsigned char w, unsigned char h) {
	unsigned char *where=donde;
	int i, j;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			//putpixel(vram, 64 + j, 64 + i, (r << 16) + (g << 8) + b);
			where[j*4] = r;
			where[j*4 + 1] = g;
			where[j*4 + 2] = b;
		}
		where+=3200;
	}
}

int main()
{
	clearScreen();
	load_idt();
	printCurrentTime();
	fillrect(screenData->framebuffer,50,90,20,60,60) ;


	//printHex(readKey());
	//printCurrentTime();

	while(1);
	return 0;
}
