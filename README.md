# plugin_registration_test
Project to test different plugin registrations for static and dynamic linking.

This project demonstrates the ability to create multiple plugin libraries,
optionally register them at startup, and demonstrate their use.  The different
scenarios include:

- Static Linking, no tool linked
- Dynamic Linking, no tool linked
- Static Linking, two tools linked in
- Dynamic Linking, two tools linked in
- Dynamic Linking, no tool linked, one tool preloaded
- Dynamic Linking, no tool linked, two tools preloaded

To demonstrate the architecture, do the following:

```bash
make
test.sh
```

You should see output like:

```bash
$ make ; ./test.sh 
gcc -O0 -g -fPIC -c main.c -o main.o
gcc -O0 -g -fPIC -c plugin.c -o plugin.o
ar -crs libplugin.a plugin.o
gcc -O0 -g -fPIC -o program_static_notool main.o libplugin.a 
gcc -O0 -g -fPIC -c tool1.c -o tool1.o
ar -crs libtool1.a tool1.o
gcc -O0 -g -fPIC -c tool2.c -o tool2.o
ar -crs libtool2.a tool2.o
gcc -O0 -g -fPIC -o program_static main.o libplugin.a -Wl,-all_load libtool1.a -Wl,-all_load libtool2.a 
gcc -shared -undefined dynamic_lookup -o libplugin.dylib plugin.o
gcc -shared -undefined dynamic_lookup -o libtool1.dylib tool1.o
gcc -shared -undefined dynamic_lookup -o libtool2.dylib tool2.o
gcc -O0 -g -fPIC -o program_dynamic main.o -L. -lplugin -ltool1 -ltool2
gcc -O0 -g -fPIC -o program_dynamic_notool main.o -L. -lplugin
##################### Static, no tool linked ####################
plugin.c void plugin_init(void)
plugin.c void plugin_function(void)
plugin.c void plugin_finalize(void)
##################### Static, tool linked    ####################
tool1.c void initme(void)
plugin.c void register_tool(plugin_pointers_t *)
Registering one
tool2.c void initme(void)
plugin.c void register_tool(plugin_pointers_t *)
Registering two
plugin.c void plugin_init(void)
tool1.c void tool_init(void)
tool2.c void tool2_init(void)
plugin.c void plugin_function(void)
tool1.c void tool_function(void)
tool2.c void tool2_function(void)
plugin.c void plugin_finalize(void)
tool1.c void tool_finalize(void)
tool2.c void tool2_finalize(void)
##################### Dynamic, no tool linked ###################
plugin.c void plugin_init(void)
plugin.c void plugin_function(void)
plugin.c void plugin_finalize(void)
##################### Dynamic, tool linked    ###################
tool1.c void initme(void)
plugin.c void register_tool(plugin_pointers_t *)
Registering one
tool2.c void initme(void)
plugin.c void register_tool(plugin_pointers_t *)
Registering two
plugin.c void plugin_init(void)
tool1.c void tool_init(void)
tool2.c void tool2_init(void)
plugin.c void plugin_function(void)
tool1.c void tool_function(void)
tool2.c void tool2_function(void)
plugin.c void plugin_finalize(void)
tool1.c void tool_finalize(void)
tool2.c void tool2_finalize(void)
##################### Dynamic, one tool preload #################
tool1.c void initme(void)
plugin.c void register_tool(plugin_pointers_t *)
Registering one
plugin.c void plugin_init(void)
tool1.c void tool_init(void)
plugin.c void plugin_function(void)
tool1.c void tool_function(void)
plugin.c void plugin_finalize(void)
tool1.c void tool_finalize(void)
##################### Dynamic, two tool preload #################
tool1.c void initme(void)
plugin.c void register_tool(plugin_pointers_t *)
Registering one
tool2.c void initme(void)
plugin.c void register_tool(plugin_pointers_t *)
Registering two
plugin.c void plugin_init(void)
tool1.c void tool_init(void)
tool2.c void tool2_init(void)
plugin.c void plugin_function(void)
tool1.c void tool_function(void)
tool2.c void tool2_function(void)
plugin.c void plugin_finalize(void)
tool1.c void tool_finalize(void)
tool2.c void tool2_finalize(void)
```