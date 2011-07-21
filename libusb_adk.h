
int mainPhase();
int init(void);
int closeHandle(void);
int chAccessoryMode(
		const char* manufacturer,
		const char* modelName,
		const char* description,
		const char* version,
		const char* url,
		const char* serialNumber);
void print_devs();
int open_accesory_dev();
#if defined(__MINGW32__)
#include <windows.h>
#define sleep Sleep
#else
#define sleep sleep
#endif

