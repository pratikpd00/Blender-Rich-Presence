//Wraps discord rich presence functionality into a python module written in C++

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "discord_files/discord.h"

using namespace std;
using namespace discord;

Core* core;

static PyObject *initRichPresence(PyObject *self, PyObject *args) {
    
}