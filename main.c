#include "plugin.h"

int main (int argc, char * argv[]) {
    plugin_init();
    plugin_function();
    plugin_finalize();
    return 0;
}
