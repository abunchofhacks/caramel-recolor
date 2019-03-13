#include "Python.h"


static PyObject* caramel_recolor(PyObject* self, PyObject* args)
{
	PyObject* data;
	PyObject* channels;

	if (!PyArg_ParseTuple(args, "OO", &data, &channels))
	{
		return NULL;
	}

	if (!PyObject_CheckBuffer(data))
	{
		fprintf(stderr, "#### Not an array buffer\n");
		return NULL;
	}

	Py_buffer buffer;
	if (PyObject_GetBuffer(data, &buffer,
		PyBUF_WRITABLE | PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT))
	{
		fprintf(stderr, "#### Not a contiguous writable array\n");
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);
		fprintf(stderr, "#### Python Error: %s\n", PyString_AsString(pvalue));
		return NULL;
	}

	if (strcmp(buffer.format, "I") != 0)
	{
		fprintf(stderr, "#### Not an array of 32bit unsigned integers\n");
		PyBuffer_Release(&buffer);
		return NULL;
	}

	if (!PyList_Check(channels))
	{
		fprintf(stderr, "#### Not a list of channels\n");
		PyBuffer_Release(&buffer);
		return NULL;
	}
	else if (PyList_Size(channels) != 5)
	{
		fprintf(stderr, "#### Does not have exactly 5 channels\n");
		PyBuffer_Release(&buffer);
		return NULL;
	}

	for (Py_ssize_t i = 0; i < buffer.len; i += buffer.itemsize)
	{
		uint32_t* color = (uint32_t*)(buffer.buf + i);
		if (*color & 0x00FFFF00)
		{
			*color = 0xFFFF00FF;
		}
	}

	PyBuffer_Release(&buffer);
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
