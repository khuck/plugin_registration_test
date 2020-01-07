#pragma once

typedef void (*plugin_init_t)(void);
typedef void (*plugin_function_t)(void);
typedef void (*plugin_finalize_t)(void);

typedef struct plugin_pointers {
    char * tool_name;
    plugin_init_t init;
    plugin_function_t function;
    plugin_finalize_t finalize;
} plugin_pointers_t;

typedef void (*plugin_register_t)(plugin_pointers_t *);

extern __attribute__((weak)) void register_tool(plugin_pointers_t * tool);
