#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <time.h>
#include <cstdio>
#include "discord_files/discord.h"

using namespace discord;

/*
 * Used for Discord activity objects in Python
 */
typedef struct {
    PyObject_HEAD;
    Activity activity;
    Core* core;
} ActivityObject;

PyObject *activity_getDetails(ActivityObject *self, void *closure) {
    PyObject *details = Py_BuildValue("s", self->activity.GetDetails());
    Py_INCREF(details);
    return details;
}

int activity_setDetails(ActivityObject *self, PyObject *value, void *closure) {
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

int activity_init(ActivityObject* self, PyObject* args, PyObject* kwds) {
    char* details = "";
    char* keywords[] = {"details", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|s", keywords, &details)) {
        return -1;
    }

    //client id is 0 to commit to a public repo
    Core::Create(0, DiscordCreateFlags_Default, &(self->core));

    self->activity.SetName("Blender");
    self->activity.SetDetails(details);
    ActivityAssets& assets = self->activity.GetAssets();
    assets.SetLargeText("Blender");
    assets.SetLargeImage("blender_icon_1024x1024");

    self->core->ActivityManager().UpdateActivity(self->activity, [](Result result) {
        if (result == Result::Ok) {
            printf("successfully started presence");
        } else {
            printf("unsuccessfully started presence");
        }
    });
}

PyObject* update(ActivityObject* self, PyObject* Py_UNUSED(ignored)) {
    self->core->ActivityManager().UpdateActivity(self->activity, [](Result result) {
        if (result == Result::Ok) {
            printf("successfully updated presence");
        } else {
            printf("unsuccessfully updated presence");
        }
    });
}

PyObject* clear(ActivityObject* self, PyObject* Py_UNUSED(ignored)) {
    self->core->ActivityManager().ClearActivity([](Result result) {
        if (result == Result::Ok) {
            printf("successfully stopped presence");
        } else {
            printf("unsuccessfully stopped presence");
        }
    });
}


static PyMethodDef ActivityMethod[] = {
    {"update", (PyCFunction) update, METH_NOARGS, "Return the name, combining the first and last name"},
    {"clear", (PyCFunction) clear,  METH_NOARGS, "Clears Blender's presence from discord"},
    {NULL}
};

static PyGetSetDef getSetters[] = {
    {"details", (getter) activity_getDetails, (setter) activity_setDetails, "The details about the Blender activity", NULL},
    {NULL}
};


PyMODINIT_FUNC PyInit_BlenderActivity() {
    PyTypeObject activityType;

    activityType.ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    activityType.tp_name = "activity.Activity";
    activityType.tp_doc = "An object that manages rich presence for Blender";
    activityType.tp_basicsize = sizeof(ActivityObject);
    activityType.tp_itemsize = 0;
    activityType.tp_flags = Py_TPFLAGS_DEFAULT;
    activityType.tp_new = PyType_GenericNew;
    activityType.tp_init = (initproc) activity_init;
    activityType.tp_methods = ActivityMethod;
    activityType.tp_getset = getSetters;

    PyModuleDef BlenderActivity;

    BlenderActivity.m_base = PyModuleDef_HEAD_INIT;
    BlenderActivity.m_name = "activity";
    BlenderActivity.m_doc = "Allows Blender's scripting engine to use Discord rich presence";
    BlenderActivity.m_size = -1;

    PyObject *module;
    if (PyType_Ready(&activityType) < 0) {
        return NULL;
    }

    module = PyModule_Create(&BlenderActivity);
    if (module == NULL) {
        return NULL;
    }

    Py_INCREF(&activityType);
    if (PyModule_AddObject(module, "Custom", (PyObject *) &activityType) < 0) {
        Py_DECREF(&activityType);
        Py_DECREF(module);
        return NULL;
    }

    return module;
}