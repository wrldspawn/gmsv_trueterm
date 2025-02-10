#include "main.h"

void __attribute__((constructor)) SO_load() { SetupListener(); }
void __attribute__((destructor)) SO_unload() { DestroyListener(); }
