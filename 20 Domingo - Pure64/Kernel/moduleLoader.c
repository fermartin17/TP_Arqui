#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>

static void loadModule(uint8_t ** module, void * targetModuleAddress);
static uint32_t readUint32(uint8_t ** address);

void loadModules(void * payloadStart, void ** targetModuleAddress)
{
	int i;
	uint8_t * currentModule = (uint8_t*)payloadStart;
	uint32_t moduleCount = readUint32(&currentModule);

	for (i = 0; i < moduleCount; i++)
		loadModule(&currentModule, targetModuleAddress[i]);
}

static void loadModule(uint8_t ** module, void * targetModuleAddress)
{
	uint32_t moduleSize = readUint32(module);

	print("  Will copy module at 0x");
	printHex((uint64_t)*module);
	print(" to 0x");
	printHex((uint64_t)targetModuleAddress);
	print(" (");
	printDec(moduleSize);
	print(" bytes)");

	memcpy(targetModuleAddress, *module, moduleSize);
	*module += moduleSize;

	print(" [Done]");
	newLine();
}

static uint32_t readUint32(uint8_t ** address)
{
	uint32_t result = *(uint32_t*)(*address);
	*address += sizeof(uint32_t);
	return result;
}
