#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>


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

int main()
{
	clearScreen();
	load_idt();
	printCurrentTime();

	//printHex(readKey());
	//printCurrentTime();

	while(1);
	return 0;
}
