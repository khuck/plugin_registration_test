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

static void initme(void) {
    plugin_pointers_t pointers;
    plugin_register_t reg_function;
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    memset(&pointers, 0, sizeof(plugin_pointers_t));
    pointers.tool_name = "one";
    pointers.init = &tool_init;
    pointers.function = &tool_function;
    pointers.finalize = &tool_finalize;
    reg_function = &register_tool;
    if (reg_function != NULL) {
        reg_function(&pointers);
    }
}

__attribute__((visibility("default")))
__attribute__((weak)) void register_tool(plugin_pointers_t * tool);
