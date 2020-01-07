#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "tool.h"

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
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    memset(&pointers, 0, sizeof(plugin_pointers_t));
    pointers.tool_name = "one";
    pointers.init = &tool_init;
    pointers.function = &tool_function;
    pointers.finalize = &tool_finalize;
    register_tool(&pointers);
}

__attribute__((visibility("default")))
__attribute__((weak)) void register_tool(plugin_pointers_t * tool)
#if defined(__clang__) && defined(__APPLE__)
{ printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__); }
#else
;
#endif
