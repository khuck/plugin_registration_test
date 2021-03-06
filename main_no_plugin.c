#include "stdlib.h"
#include "stdio.h"
#include "plugin.h"
#include "prettyprint.h"

/* This example tests the case where the application does NOT
   have the plugin library linked in, but may or may not have
   the tool libraries linked, and may or may not have the tool
   libraries preloaded. */

int main (int argc, char * argv[]) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    printf("(no other output expected...)\n");
    return 0;
}
