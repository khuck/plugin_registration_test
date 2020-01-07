#include "stdlib.h"
#include "stdio.h"
#include "plugin.h"
#include "tool.h"

/* Assume only two tools for this test. */

plugin_init_t init_funcs[2] = {NULL};
plugin_function_t function_funcs[2] = {NULL};
plugin_finalize_t finalize_funcs[2] = {NULL};
int num_tools = 0;

void plugin_init(void) {
    int i;
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    for (i = 0 ; i < num_tools ; i++) {
        init_funcs[i]();
    }
}

void plugin_function(void) {
    int i;
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    for (i = 0 ; i < num_tools ; i++) {
        function_funcs[i]();
    }
}

void plugin_finalize(void) {
    int i;
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    for (i = 0 ; i < num_tools ; i++) {
        finalize_funcs[i]();
    }
}

void register_tool(plugin_pointers_t * pointers) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    printf("Registering %s\n", pointers->tool_name);
    init_funcs[num_tools] = pointers->init;
    function_funcs[num_tools] = pointers->function;
    finalize_funcs[num_tools] = pointers->finalize;
    num_tools = num_tools + 1;
}

