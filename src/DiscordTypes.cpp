#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "discord_files/discord.h"

using namespace discord;

/*
 * Used for Discord activity objects in Python
 */
typedef struct activityObject {
    PyObject_HEAD
    Activity activity;
} activityObject;



PyObject *activity_getAppId(activityObject *self, void *closure) {
    PyObject *id = Py_BuildValue("i", self->activity.GetApplicationID());
    Py_INCREF(id);
    return id;
}

PyObject *activity_getName(activityObject *self, void *closure) {
    PyObject *name = Py_BuildValue("s", self->activity.GetName());
    Py_INCREF(name);
    return name;
}

PyObject *activity_getState(activityObject *self, void *closure) {
    PyObject *state = Py_BuildValue("i", self->activity.GetState());
    Py_INCREF(state);
    return state;
}

PyObject *activity_getDetails(activityObject *self, void *closure) {
    PyObject *details = Py_BuildValue("s", self->activity.GetDetails());
    Py_INCREF(details);
    return details;
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

int activity_setState(activityObject *self, PyObject *value, void *closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "cannot delete the name of an activity");
        return -1;
    }

    char* state;
    if (!PyArg_Parse(value, "s", &state)) {
        PyErr_SetString(PyExc_TypeError, "can only set activity.state to an int");
        return -1
    }

    self.activity.SetState(state);
}

int activity_setDetails(activityObject *self, PyObject *value, void *closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "cannot delete the name of an activity");
        return -1;
    }

    char* details;
    if (!PyArg_Parse(value, "s", &details)) {
        PyErr_SetString(PyExc_TypeError, "can only set activity.state to an int");
        return -1
    }

    self.activity.SetState(details);
}