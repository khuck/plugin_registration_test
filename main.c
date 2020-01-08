#include "stdlib.h"
#include "stdio.h"
#include "plugin.h"
#include "prettyprint.h"

/* This example tests the case where the application has the plugin
   library linked in, but may or may not have the tool libraries
   linked, and may or may not have the tool libraries preloaded. */

int main (int argc, char * argv[]) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    plugin_init_();
    plugin_function_();
    plugin_finalize_();
    return 0;
}
