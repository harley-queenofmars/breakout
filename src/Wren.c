#include "Wren.h"
#include "wren.h"

void getConfig();
static void wrenWriteFn(WrenVM* vm, 
	const char* text);

void wrenErrorFn(WrenVM* vm, 
	WrenErrorType errorType,
    const char* module, 
	const int line,
    const char* msg);

WrenLoadModuleResult wrenLoadModuleFn(WrenVM* vm, 
	const char* name);

WrenForeignClassMethods wrenBindForeignClassFn(WrenVM* vm, 
	const char* module, 
	const char* className);

WrenForeignMethodFn wrenBindForeignMethodFn(WrenVM* vm,
    const char* module, 
	const char* className, 
	bool isStatic,
    const char* signature);

const char* wrenResolveModuleFn(WrenVM* vm,
    const char* importer, const char* name);

static const char* module = "main";
enum Slot : int {
    SlotName,
    SlotVersion,
    SlotPlayerVelocity,
    SlotBallVelocity,
    SlotIndexX,
    SlotIndexY,
    SlotX,
    SlotY,
    SlotEOT
};


class(Wren);

void* method Ctor(WrenRef this)
{
	this->vm = wrenNewVM(&(WrenConfiguration){
		.writeFn = &wrenWriteFn,
		.errorFn = &wrenErrorFn,
		.loadModuleFn = &wrenLoadModuleFn,
		.bindForeignClassFn = &wrenBindForeignClassFn,
		.bindForeignMethodFn = &wrenBindForeignMethodFn,
		.resolveModuleFn = &wrenResolveModuleFn,
		.heapGrowthPercent = 0,
		.initialHeapSize = 0,
		.minHeapSize = 0,
		.reallocateFn = nullptr,
		.userData = nullptr
	});
  
    CFStringRef script = CFFS.readTextFile((char*)"Resources/script/main.wren");
	WrenInterpretResult result = wrenInterpret(this->vm, module, cstr(script));
  
	switch (result) {
	case WREN_RESULT_COMPILE_ERROR:
		printf("Compile Error!\n");
		break;
	case WREN_RESULT_RUNTIME_ERROR:
		printf("Runtime Error!\n");
		break;
	case WREN_RESULT_SUCCESS:
		printf("Success!\n"); 
		break;
	}
	wrenEnsureSlots(this->vm, SlotEOT);
    wrenGetVariable(this->vm, module, "name", SlotName);
	wrenGetVariable(this->vm, module, "version", SlotVersion);
    wrenGetVariable(this->vm, module, "player_velocity", SlotPlayerVelocity);
    wrenGetVariable(this->vm, module, "ball_velocity", SlotBallVelocity);
    wrenSetSlotString(this->vm, SlotIndexX, "x");
    wrenSetSlotString(this->vm, SlotIndexY, "y");
    wrenGetMapValue(this->vm, SlotBallVelocity, SlotIndexX, SlotX);
    wrenGetMapValue(this->vm, SlotBallVelocity, SlotIndexY, SlotY);

	this->name = wrenGetSlotHandle(this->vm, SlotName);
	this->version = wrenGetSlotHandle(this->vm, SlotVersion);
	this->playerVelocity = wrenGetSlotHandle(this->vm, SlotPlayerVelocity);
	this->ballVelocityX = wrenGetSlotHandle(this->vm, SlotX);
	this->ballVelocityY = wrenGetSlotHandle(this->vm, SlotY);

    return this;
}

method const char* GetName(WrenRef this)
{
    return wrenGetSlotString(this->vm, SlotName);
}

method double GetVersion(WrenRef this)
{
	return wrenGetSlotDouble(this->vm, SlotVersion);
}

method double GetPlayerVelocity(WrenRef this)
{
	wrenSetSlotHandle(this->vm, SlotPlayerVelocity, this->playerVelocity);
	return wrenGetSlotDouble(this->vm, SlotPlayerVelocity);
}

method Vec2 GetBallVelocity(WrenRef this)
{
	wrenSetSlotHandle(this->vm, SlotX, this->ballVelocityX);
	wrenSetSlotHandle(this->vm, SlotY, this->ballVelocityY);
    return (Vec2){wrenGetSlotDouble(this->vm, SlotX), wrenGetSlotDouble(this->vm, SlotY)};
}


static void wrenWriteFn(WrenVM* vm, 
	const char* text)
{
  printf("%s", text);
}

void wrenErrorFn(WrenVM* vm, 
	WrenErrorType errorType,
	const char* module, 
	const int line,
	const char* msg)
{
	switch (errorType) {
    case WREN_ERROR_COMPILE:
      	printf("[%s line %d] [Error] %s\n", module, line, msg);
      	break;
    case WREN_ERROR_STACK_TRACE:
      	printf("[%s line %d] in %s\n", module, line, msg);
      	break;
    case WREN_ERROR_RUNTIME:
      	printf("[Runtime Error] %s\n", msg);
      	break;
  	}
}

WrenLoadModuleResult wrenLoadModuleFn(WrenVM* vm, 
	const char* name)
{
	CFStringRef path = NewString((char*)name);
	printf("%s\n", cstr(path));

	CFStringRef text = CFFS.readTextFile(cstr(path));
	printf("%s\n", cstr(text));

	return (WrenLoadModuleResult){
		.source = cstr(text)
	};
}

WrenForeignClassMethods wrenBindForeignClassFn(WrenVM* vm, 
	const char* module, 
	const char* className)
{
	return (WrenForeignClassMethods){0};
}

WrenForeignMethodFn wrenBindForeignMethodFn(WrenVM* vm,
    const char* module, 
	const char* className, 
	bool isStatic,
    const char* signature)
{
	return (WrenForeignMethodFn){0};
}


const char* wrenResolveModuleFn(WrenVM* vm,
    const char* importer, 
	const char* name)
{
	CFStringRef path = NewString(CFStringJoin(3, "Resources/script", name, ".wren"));
	printf("%s\n", cstr(path));
	return cstr(path);
}
