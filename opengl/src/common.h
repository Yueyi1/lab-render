#ifndef COMMON_H
#define COMMON_H

#define DEBUG // Define DEBUG before you include debug_toolkits.h

#ifdef _DEBUG
#include "debug_toolkits.h"
#endif /* _DEBUG */

#ifdef DEBUG
#else
#define DEBUG_PRINTF(...)
#define ERR_PRINT(...)
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#endif // COMMON_H