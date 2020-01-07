#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "tool.h"

static void __attribute__((constructor)) initme(void);

void tool2_init(void) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
}

void tool2_function(void) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
}

void tool2_finalize(void) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
}

static void initme(void) {
    plugin_pointers_t pointers;
    memset(&pointers, 0, sizeof(plugin_pointers_t));
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    pointers.tool_name = "two";
    pointers.init = &tool2_init;
    pointers.function = &tool2_function;
    pointers.finalize = &tool2_finalize;
    register_tool(&pointers);
}

