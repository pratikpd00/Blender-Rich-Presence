//Wraps discord rich presence functionality into a python module written in C++

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "discord_files/discord.h"

using namespace std;
using namespace discord;

Core* core;

/*
 * A Python method to start rich presence for discord
 */
static PyObject *updateRichPresence(PyObject *self, PyObject *args, PyObject *kws) {
    char* keywords[] = {"activity", NULL};
    Activity activity;

    if (!PyArg_ParseTupleAndKeywords(args, kws, "o", keywords, convertToActivity, (void *)&activity)) {
        return NULL;
    }

    Py_RETURN_NONE
    
}

int convertToActivity(PyObject *object, void *activity) {
    Activity *actPointer = (Activity *)activity;

}

int convertToTimeStamp(PyObject *object, void *timestamp) {
    ActivityTimestamps *timePointer = (ActivityTimestamps *)timestamp;
}



/*
 * Method list for the python module
 */
static PyMethodDef methods[] {
    {"update_rich_presence", (PyCFunction)(void (*)(void)) initRichPresence, METH_VARARGS | METH_KEYWORDS, ""},
    {NULL, NULL, 0, NULL}
};