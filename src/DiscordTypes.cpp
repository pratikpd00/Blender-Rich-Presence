#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "discord_files/discord.h"


/*
 * Used for Discord activity objects in Python
 */
typedef struct activityObject {
    PyObject_HEAD
    Activity activity;
} activityObject;



PyObject *activity_getAppId(activityObject *self, void *closure) {
    PyObject *id = Py_BuildValue("i", self->activty.GetApplicationID());
    Py_INCREF(id);
    return id;
}

PyObject *activity_getName(activityObject *self, void *closure) {
    PyObject *name = Py_BuildValue("s", self->activty.GetName());
    Py_INCREF(name);
    return name;
}

PyObject *activity_getState(activityObject *self, void *closure) {
    PyObject *state = Py_BuildValue("s", self->activty.GetState());
    Py_INCREF(state);
    return state;
}

int activity_setName(activityObject *self, PyObject *value, void *closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "cannot delete the name of an activity");
        return -1;
    }

    char* name;
    if (!PyArg_Parse(value, "s", &name)) {
        PyErr_SetString(PyExc_TypeError, "can only set activity.name to a string");
        return -1
    }

    self.activity.SetName(name);
}