
#include "log.hpp"

/*
 * message, error code (1 - error, halt; 0 - warning, cont.)
 */
void __log(const char *string, int code)
{
    if (code >= 1) {
        printf("[UR] ERROR :: %s || halted.\n", string); 
        exit(1);
    }

    else {
        printf("[UR] %s\n", string);
    }
}
