#include "stdlib.h"
#include "stdio.h"
#include "plugin.h"
#include "tool.h"
#include "prettyprint.h"

/* This is a prototype implementation of an API to add a plugin
   interface to a library or application. */

/* Assume only two tools for this test. */

plugin_init_t init_funcs[2] = {NULL};
plugin_function_t function_funcs[2] = {NULL};
plugin_finalize_t finalize_funcs[2] = {NULL};
int num_tools = 0;

/* For each tool registered, call the initialization function
   for the tool library */

void plugin_init(void) {
    int i;
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    for (i = 0 ; i < num_tools ; i++) {
        init_funcs[i]();
    }
}

/* For each tool registered, call the example function
   for the tool library */

void plugin_function(void) {
    int i;
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    for (i = 0 ; i < num_tools ; i++) {
        function_funcs[i]();
    }
}

/* For each tool registered, call the finalize function
   for the tool library */

void plugin_finalize(void) {
    int i;
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    for (i = 0 ; i < num_tools ; i++) {
        finalize_funcs[i]();
    }
}

/* Each tool will register with the plugin interface when
   they are loaded, using a static global initializer function
   to call this tool registration function */

void register_tool(plugin_pointers_t * pointers) {
    printf("%s %s\n", __FILE__, __PLUGIN_FUNCTION__);
    printf("Registering %s\n", pointers->tool_name);
    init_funcs[num_tools] = pointers->init;
    function_funcs[num_tools] = pointers->function;
    finalize_funcs[num_tools] = pointers->finalize;
    num_tools = num_tools + 1;
}

/* Create Fortran bindings! */

void plugin_init_(void) { plugin_init(); }
void plugin_function_(void) { plugin_function(); }
void plugin_finalize_(void) { plugin_finalize(); }
