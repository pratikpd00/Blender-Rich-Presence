#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <time.h>
#include "discord_files/discord.h"

using namespace discord;

/*
 * Used for Discord activity objects in Python
 */
typedef struct {
    PyObject_HEAD;
    Activity activity;
    Core* core;
} activityObject;


static PyTypeObject activityType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "activity.Activity",
    .tp_doc = "An object that manages rich presence for Blender",
    .tp_basicsize = sizeof(activityObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
};

PyObject *activity_getDetails(activityObject *self, void *closure) {
    PyObject *details = Py_BuildValue("s", self->activity.GetDetails());
    Py_INCREF(details);
    return details;
}

int activity_setDetails(activityObject *self, PyObject *value, void *closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "cannot delete the name of an activity");
        return -1;
    }

    char* details;
    if (!PyArg_Parse(value, "s", &details)) {
        PyErr_SetString(PyExc_TypeError, "can only set activity.state to an int");
        return -1;
    }

    self->activity.SetState(details);
}

int activity_init(activityObject* self, PyObject* args, PyObject* kwds) {
    char* details = "";
    char* keywords[] = {"details", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|s", keywords, &details)) {
        return -1;
    }

    //client id is 0 to upload to public repo
    Core::Create(0, DiscordCreateFlags_Default, &(self->core));

    self->activity.SetName("Blender");
    self->activity.SetDetails(details);
    ActivityAssets& assets = self->activity.GetAssets();
    assets.SetLargeText("Blender");
    assets.SetLargeImage("resources/blender_logo.png");

}