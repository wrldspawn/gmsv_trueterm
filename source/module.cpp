#include "main.h"
#include <GarrysMod/Lua/Interface.h>

GMOD_MODULE_OPEN() {
  SetupListener();
  return 0;
}

GMOD_MODULE_CLOSE() {
  DestroyListener();
  return 0;
}
