// This wires up all of the foreign classes and methods defined by the built-in
// modules bundled with the CLI.
#pragma once
#include "../libs/corefx/corefx.h"      // IWYU pragma: keep
#include "../libs/corefw/corefw.h"      // IWYU pragma: keep
#include "wren.h"					    // IWYU pragma: keep
	
// Returns the source for built-in module [name].
WrenLoadModuleResult loadBuiltInModule(const char* module);
void loadModuleComplete(WrenVM* vm, const char* name, struct WrenLoadModuleResult result);

// Looks up a foreign method in a built-in module.
//
// Returns `NULL` if [moduleName] is not a built-in module.
WrenForeignMethodFn bindBuiltInForeignMethod(
    WrenVM* vm, const char* moduleName, const char* className, bool isStatic,
    const char* signature);

// Binds foreign classes declared in a built-in modules.
WrenForeignClassMethods bindBuiltInForeignClass(
    WrenVM* vm, const char* moduleName, const char* className);


extern void directoryList(WrenVM* vm);
extern void directoryCreate(WrenVM* vm);
extern void directoryDelete(WrenVM* vm);
extern void fileAllocate(WrenVM* vm);
extern void fileFinalize(void* data);
extern void fileDelete(WrenVM* vm);
extern void fileOpen(WrenVM* vm);
extern void fileSizePath(WrenVM* vm);
extern void fileClose(WrenVM* vm);
extern void fileDescriptor(WrenVM* vm);
extern void fileReadBytes(WrenVM* vm);
extern void fileRealPath(WrenVM* vm);
extern void fileSize(WrenVM* vm);
extern void fileStat(WrenVM* vm);
extern void fileWriteBytes(WrenVM* vm);
