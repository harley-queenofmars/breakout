// This wires up all of the foreign classes and methods defined by the built-in
// modules bundled with the CLI.
#pragma once
#include <corefx.h>      // IWYU pragma: keep
#include <corefw.h>      // IWYU pragma: keep
#include "wren.h"					    // IWYU pragma: keep
	
// Returns the source for built-in module [name].
/**
 * @brief Loads a built-in Wren module by its name.
 *
 * This function attempts to load a built-in module for the Wren virtual machine,
 * identified by the provided module name.
 *
 * @param module The name of the module to load.
 * @return WrenLoadModuleResult The result of the module loading operation, containing
 *         the module's source code and user data if successful.
 */
WrenLoadModuleResult loadBuiltInModule(const char* module);


void loadModuleComplete(
    WrenVM* vm, const char* name, struct WrenLoadModuleResult result);

// Looks up a foreign proc in a built-in module.
//
// Returns `NULL` if [moduleName] is not a built-in module.
/**
 * Binds a built-in foreign method to a Wren class or module.
 *
 * This function is used by the Wren VM to resolve and bind a C/C++ function
 * as the implementation of a foreign method declared in Wren code.
 *
 * @param vm         Pointer to the Wren virtual machine instance.
 * @param moduleName Name of the Wren module containing the class.
 * @param className  Name of the Wren class containing the method.
 * @param isStatic   True if the method is static, false if it is an instance method.
 * @param signature  The Wren method signature (e.g., "foo(_)" or "bar()").
 * @return           A pointer to the C function implementing the foreign method,
 *                   or nullptr if no matching method is found.
 */
WrenForeignMethodFn bindBuiltInForeignMethod(
    WrenVM* vm, const char* moduleName, const char* className, bool isStatic,
    const char* signature);

// Binds foreign classes declared in a built-in modules.
/**
 * Binds a built-in foreign class to the Wren VM.
 *
 * This function is used to associate a foreign class implementation with a specific
 * module and class name in the Wren scripting environment. It returns the methods
 * required by the Wren VM to manage the foreign class.
 *
 * @param vm         Pointer to the Wren virtual machine instance.
 * @param moduleName Name of the Wren module containing the class.
 * @param className  Name of the foreign class to bind.
 * @return           A WrenForeignClassMethods struct containing pointers to the
 *                   allocation and finalization functions for the foreign class.
 */
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
