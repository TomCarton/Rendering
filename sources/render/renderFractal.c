// renderFractal.c
//
// written by Thomas CARTON
//

#include <math.h>

#include "renderFractal.h"


static unsigned int FractalEscape(double zr, double zi, double cr, double ci, int maxIterations)
{
	unsigned int age = 0;
	
	while (age++ < maxIterations && zr * zr + zi * zi <= 2 * 2)
	{
		double r = zr;
		double i = zi;

		zr = r * r - i * i + cr;
		zi = 2 * r * i + ci;
	}

	return age - 1;
}

void RenderFractal(FractalParameters params, unsigned char *buffer, unsigned int width, unsigned int height)
{
	double z0r = 0, z0i = 0;
	double cr = params.cr, ci = params.ci;

	for (unsigned int k = 0; k < width * height; ++k)
	{
		unsigned int x = k % width;
		unsigned int y = k / width;

		double fx = params.xMin + (x + 0.5) / width * (params.xMax - params.xMin);
		double fy = params.yMax - (y + 0.5) / height * (params.yMax - params.yMin);

		switch (params.mode)
		{
			case FractalModeMandelbrot:
				cr = fx;
				ci = fy;
				break;

			case FractalModeJulia:
				z0r = fx;
				z0i = fy;
				break;
		}

		double j = (double)FractalEscape(z0r, z0i, cr, ci, params.iterations) / params.iterations;
		buffer[k * 3 + 0] = (unsigned char)(pow(j, 0.6) * 255 + 0.5);
		buffer[k * 3 + 1] = (unsigned char)(pow(j, 0.3) * 255 + 0.5);
		buffer[k * 3 + 2] = (unsigned char)(pow(j, 0.1) * 255 + 0.5);
	}
}
