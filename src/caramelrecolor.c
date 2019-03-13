#include "Python.h"


static PyObject* caramel_recolor(PyObject* self, PyObject* args)
{
	return Py_None;
}

static PyMethodDef CaramelMethods[] = {
	{"recolor", caramel_recolor, METH_VARARGS,
		"Recolor an image using five channels."},
	{NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initcaramelrecolor(void)
{
    (void) Py_InitModule("caramelrecolor", CaramelMethods);
}
