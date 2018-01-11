#ifndef OWNCRAFT_SYSTEM_H
#define OWNCRAFT_SYSTEM_H

#ifdef _MSC_VER
#	pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // _MSC_VER

void init_console();

#endif // OWNCRAFT_SYSTEM_H