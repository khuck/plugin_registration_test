#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "tool.h"
#include "prettyprint.h"

static void __attribute__((constructor)) initme(void);

void tool_init(void) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
}

void tool_function(void) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
}

void tool_finalize(void) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
}

/* What's happening here?  Well, we check to see if
   the registration function is our own weak (and undefined)
   version of the function, or if the plugin library exists
   in the application.  this checks the case when this tool
   is linked into an appliation without the plugin support. */

static void initme(void) {
    plugin_pointers_t pointers;
    plugin_register_t reg_function;
    reg_function = &register_tool;
    if (reg_function != NULL) {
        printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
        memset(&pointers, 0, sizeof(plugin_pointers_t));
        pointers.tool_name = "one";
        pointers.init = &tool_init;
        pointers.function = &tool_function;
        pointers.finalize = &tool_finalize;
        reg_function(&pointers);
    }
}

__attribute__((visibility("default")))
__attribute__((weak)) void register_tool(plugin_pointers_t * tool);
