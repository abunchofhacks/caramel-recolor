# Caramel Recolor

This is the Caramel Recolor library
developed by [A Bunch of Hacks](https://github.com/abunchofhacks)
and commissioned by [Joseph Hewitt](https://github.com/jwvhewitt).

This library reimplements a gradient-based recoloring algorithm used in [Gearhead Caramel](https://github.com/jwvhewitt/gearhead-caramel/).
Its sole method, `caramelrecolor.recolor()` takes two arguments:
the first a contiguous array (e.g. a `numpy.array`) of 32-bit ARGB color values,
where A is unused and each of R, G and B is either zero or equal to all other non-zero values;
the second a list of [Gradients](https://github.com/jwvhewitt/gearhead-caramel/blob/master/pbge/image.py)
indicating the colors to use for the red, yellow, green, cyan and magenta pixels of the source image.
Blue pixels are unaffected, as blue is used within Gearhead Caramel to indicate transparency.

## Getting Started

Build with `python setup.py build` and install with `python setup.py install`.

Example usage, assuming `surface` is a [PyGame Surface](https://www.pygame.org/docs/ref/surface.html) and `color_channels` an appropriate list of channels:
```Python
    import pygame
    import numpy
    import caramelrecolor

    dims = (surface.get_width(), surface.get_height())
    data = numpy.zeros(dims, numpy.uint32)
    pygame.pixelcopy.surface_to_array(data, surface)
    caramelrecolor.recolor(data, color_channels)
    pygame.pixelcopy.array_to_surface(surface, data)
```

## License

The project license is specified in `COPYING` and `COPYING.LESSER`.

This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License (LGPL) as published
by the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
License for more details.
