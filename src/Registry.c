#include "Registry.h"

// Describes one foreign method in a class.
typedef struct
{
  bool isStatic;
  const char* signature;
  WrenForeignMethodFn fn;
} MethodRegistry;

// Describes one class in a built-in module.
typedef struct
{
  const char* name;

  MethodRegistry methods[14];
} ClassRegistry;

// Describes one built-in module.
typedef struct
{
  // The name of the module.
  const char* name;

  // Pointer to the string containing the source code of the module. We use a
  // pointer here because the string variable itself is not a constant
  // expression so can't be used in the initializer below.
  const char **source;

  ClassRegistry classes[6];
} ModuleRegistry;

static ModuleRegistry modules[] =
{ "io", nullptr, {//} &ioModuleSource, {
	{ "Directory", {
		{ true, "create_(_,_)", directoryCreate },
		{ true, "delete_(_,_)", directoryDelete },		
		{ true, "list_(_,_)", directoryList },
		{ false, nullptr, nullptr } } },
		
	{"File", {
		{ true, "<allocate>", (WrenForeignMethodFn)fileAllocate },
		{ true, "<finalize>", (WrenForeignMethodFn)fileFinalize },
		{ true, "delete_(_,_)", fileDelete },
		{ true, "open_(_,_,_)", fileOpen },
		{ true, "realPath_(_,_)", fileRealPath },
		{ true, "sizePath_(_,_)", fileSizePath },
		{ false, "close_(_)", fileClose },
		{ false, "descriptor", fileDescriptor },
		{ false, "readBytes_(_,_,_)", fileReadBytes },
		{ false, "size_(_)", fileSize },
		{ false, "stat_(_)", fileStat },
		{ false, "writeBytes_(_,_,_)", fileWriteBytes },
		{ false, nullptr, nullptr } } },
	{ nullptr, { { false, nullptr, nullptr } } },
{ nullptr, false, nullptr } } } ;
