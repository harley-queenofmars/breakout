#include "../libs/corefw/corefw.h"      // IWYU pragma: keep
#include "wren.h"						// IWYU pragma: keep
#include <stdio.h>

static void writeFn(WrenVM* vm, const char* text)
{
  printf("%s", text);
}

void errorFn(WrenVM* vm, WrenErrorType errorType,
             const char* module, const int line,
             const char* msg)
{
  switch (errorType)
  {
    case WREN_ERROR_COMPILE:
    {
      printf("[%s line %d] [Error] %s\n", module, line, msg);
    } break;
    case WREN_ERROR_STACK_TRACE:
    {
      printf("[%s line %d] in %s\n", module, line, msg);
    } break;
    case WREN_ERROR_RUNTIME:
    {
      printf("[Runtime Error] %s\n", msg);
    } break;
  }
}
int main(int argc, char *argv[])
{

	CFRefPoolRef pool = CFNew(CFRefPool);


	WrenConfiguration config;
	wrenInitConfiguration(&config);
	  config.writeFn = &writeFn;
	  config.errorFn = &errorFn;
	WrenVM* vm = wrenNewVM(&config);
  
	const char* module = "main";
	// const char* script = "System.print(\"I am running in a VM!\")";
  

    CFStringRef script = CFFS.readTextFile((char*)"Resources/src/mandelbrot.wren");
	WrenInterpretResult result = wrenInterpret(vm, module, cstr(script));

  
	switch (result) {
	  case WREN_RESULT_COMPILE_ERROR:
		{ printf("Compile Error!\n"); } break;
	  case WREN_RESULT_RUNTIME_ERROR:
		{ printf("Runtime Error!\n"); } break;
	  case WREN_RESULT_SUCCESS:
		{ printf("Success!\n"); } break;
	}
  
	// void wrenGetVariable(WrenVM* vm, const char* module,
	// 	const char* name, int slot);

	wrenEnsureSlots(vm, 10);
	wrenGetVariable(vm, "main", "yMin", 0);
	double d = wrenGetSlotDouble(vm, 0);

	printf("d = %f\n", d);

	wrenFreeVM(vm);

	CFUnref(pool);

	return 0;
}

