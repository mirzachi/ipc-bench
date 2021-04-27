extern "C" {
#include "common/parent.h"
}

int main(int argc, char* argv[]) {
    setup_parent("dbus", argc, argv);
}
