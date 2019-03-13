#include "Python.h"


static const int NUM_CHANNELS = 5;
static const int VALUES_PER_CHANNEL = 6;

enum
{
	RED,
	YELLOW,
	GREEN,
	CYAN,
	MAGENTA,
};

static inline uint8_t generate_value(uint8_t vmax, uint8_t vmin, uint8_t level)
{
	return vmin + ((vmax - vmin) * level / 215);
}

static inline uint32_t generate_color(uint8_t channel[VALUES_PER_CHANNEL],
	uint8_t level)
{
	level = (level > 40) ? (level - 40) : 0;
	uint8_t r = generate_value(channel[0], channel[3], level);
	uint8_t g = generate_value(channel[1], channel[4], level);
	uint8_t b = generate_value(channel[2], channel[5], level);
	return (r << 16) | (g << 8) | b;
}

static inline uint32_t determine_color(
	uint8_t channels[NUM_CHANNELS][VALUES_PER_CHANNEL], uint32_t color)
{
	uint8_t r = 0xFF & (color >> 16);
	uint8_t g = 0xFF & (color >> 8);
	uint8_t b = 0xFF & color;
	if      ( r && !g && !b) return generate_color(channels[RED], r);
	else if ( r &&  g && !b) return generate_color(channels[YELLOW], r);
	else if ( r && !g &&  b) return generate_color(channels[MAGENTA], r);
	else if (!r &&  g && !b) return generate_color(channels[GREEN], g);
	else if (!r &&  g &&  b) return generate_color(channels[CYAN], g);
	else return color;
}

static PyObject* caramel_recolor(PyObject* self, PyObject* args)
{
	// Get the data.
	PyObject* data;
	PyObject* channels;

	if (!PyArg_ParseTuple(args, "OO", &data, &channels))
	{
		return NULL;
	}

	if (!PyObject_CheckBuffer(data))
	{
		PyErr_SetString(PyExc_RuntimeError,
			"data is not an array buffer");
		return NULL;
	}

	Py_buffer buffer;
	if (PyObject_GetBuffer(data, &buffer,
		PyBUF_WRITABLE | PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT))
	{
		if (!PyErr_Occurred())
		{
			PyErr_SetString(PyExc_RuntimeError,
				"data is not a contiguous writable array");
		}
		return NULL;
	}

	if (strcmp(buffer.format, "I") != 0)
	{
		PyErr_SetString(PyExc_RuntimeError,
			"data is not an array of 32bit unsigned integers");
		PyBuffer_Release(&buffer);
		return NULL;
	}

	if (!PyList_Check(channels))
	{
		PyErr_SetString(PyExc_RuntimeError,
			"channels is not a list of gradients");
		PyBuffer_Release(&buffer);
		return NULL;
	}
	else if (PyList_Size(channels) != NUM_CHANNELS)
	{
		PyErr_SetString(PyExc_RuntimeError,
			"channels contains wrong number of gradients");
		PyBuffer_Release(&buffer);
		return NULL;
	}

	uint8_t channeldata[NUM_CHANNELS][VALUES_PER_CHANNEL];
	for (Py_ssize_t i = 0; i < NUM_CHANNELS; i++)
	{
		PyObject* item = PyList_GetItem(channels, i);
		if (!PyObject_HasAttrString(item, "COLOR_RANGE"))
		{
			PyErr_SetString(PyExc_RuntimeError,
				"missing COLOR_RANGE attribute");
			PyBuffer_Release(&buffer);
			return NULL;
		}

		PyObject* range = PyObject_GetAttrString(item, "COLOR_RANGE");
		if (!range)
		{
			PyErr_SetString(PyExc_RuntimeError,
				"broken COLOR_RANGE attribute");
			PyBuffer_Release(&buffer);
			return NULL;
		}

		if (!PyTuple_Check(range))
		{
			PyErr_SetString(PyExc_RuntimeError,
				"COLOR_RANGE is not a tuple");
			PyBuffer_Release(&buffer);
			return NULL;
		}
		else if (PyTuple_Size(range) != VALUES_PER_CHANNEL)
		{
			PyErr_SetString(PyExc_RuntimeError,
				"wrong number of values in COLOR_RANGE");
			PyBuffer_Release(&buffer);
			return NULL;
		}

		for (Py_ssize_t j = 0; j < VALUES_PER_CHANNEL; j++)
		{
			PyObject* val = PyTuple_GetItem(range, j);
			if (!PyInt_Check(val))
			{
				PyErr_SetString(PyExc_RuntimeError,
					"COLOR_RANGE contains non-integer values");
				PyBuffer_Release(&buffer);
				return NULL;
			}

			long x = PyInt_AsLong(val);
			if (x < 0)
			{
				PyErr_SetString(PyExc_RuntimeError,
					"COLOR_RANGE contains incorrect values");
				PyBuffer_Release(&buffer);
				return NULL;
			}

			channeldata[i][j] = (x & 0xFF);
		}
	}

	// Process the data.
	for (Py_ssize_t i = 0; i < buffer.len; i += buffer.itemsize)
	{
		uint32_t* color = (uint32_t*)(buffer.buf + i);
		*color = determine_color(channeldata, *color);
	}

	// Done.
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
