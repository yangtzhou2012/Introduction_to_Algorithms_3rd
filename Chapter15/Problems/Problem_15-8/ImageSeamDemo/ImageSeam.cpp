#include "stdafx.h"
#include "ImageSeam.h"
#include <stdexcept>
#include <ctime>


using namespace std;


ImageSeam::ImageSeam() : width(0), height(0), disruption(NULL), seamChain(NULL), totalDisruption(0)
{

}

ImageSeam::ImageSeam(int w, int h) : width(0), height(0), disruption(NULL), seamChain(NULL), totalDisruption(0)
{
	SetSize(w, h);
}

ImageSeam::~ImageSeam()
{
	Clear();
}

bool ImageSeam::SetSize(int w, int h)
{
	// The image must include at least 2 columns
	if (w <= 1 || h <= 0)
		return false;

	if (w*h != width*height || disruption == NULL)
	{
		delete[] disruption;
		disruption = new unsigned char[w*h];
	}

	if (seamChain != NULL)
	{
		delete[] seamChain;
		seamChain = NULL;
	}

	memset(disruption, 0, w*h);

	width = w;
	height = h;
	totalDisruption = 0;

	return true;
}

void ImageSeam::Clear()
{
	width = 0;
	height = 0;
	totalDisruption = 0;
	if (disruption != NULL) delete[] disruption;
	if (seamChain != NULL) delete[] seamChain;
}

void ImageSeam::GenerateRandomDisruption()
{
	srand((unsigned int)time(0));

	for (int i = 0; i < width*height; ++i)
		disruption[i] = rand() % DISRUPTION_MAX;

	if (seamChain != NULL)
	{
		delete[] seamChain;
		seamChain = NULL;
	}

	totalDisruption = 0;
}

bool ImageSeam::SetDisruption(int x, int y, unsigned char d)
{
	if (x >= 0 && x < width && y >= 0 && y < height && d <= DISRUPTION_MAX && disruption != NULL)
	{
		disruption[x+y*width] = d;
		return true;
	}
	else
		return false;
}

const unsigned char ImageSeam::GetDisruption(int x, int y) const
{
	if (x >= 0 && x < width && y >= 0 && y < height && disruption != NULL)
		return disruption[x+y*width];
	else
		throw runtime_error("");
}

bool ImageSeam::BuildImageSeam()
{
	if (width <= 1 || height <= 0 || disruption == NULL)
		return false;

	int *seamDisruption = new int[width*height];
	char *link = new char[width*height];

	unsigned char *pd = disruption;
	int *psd = seamDisruption;
	char *pl = link + width;

	for (int j = 0; j < width; ++j)
		*psd++ = *pd++;

	for (int i = 1; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			*psd = *(psd-width);
			*pl = 0;

			if (j != 0)
			{
				if (*(psd-width-1) < *psd)
				{
					*psd = *(psd-width-1);
					*pl = -1;
				}
			}

			if (j != width-1)
			{
				if (*(psd-width+1) < *psd)
				{
					*psd = *(psd-width+1);
					*pl = 1;
				}
			}

			*psd += *pd;
			pd++;
			psd++;
			pl++;
		}
	}

	psd = seamDisruption + (height-1)*width;
	int lastSeamDisruption = *psd++;
	int lastIndex = 0;

	for (int j = 1; j < width; ++j)
	{
		if (*psd < lastSeamDisruption)
		{
			lastSeamDisruption = *psd;
			lastIndex = j;
		}

		psd++;
	}

	if (seamChain == NULL) seamChain = new int[height];
	seamChain[height-1] = lastIndex;
	totalDisruption = lastSeamDisruption;
	pl = link + (height-1)*width + lastIndex;

	for (int i = height-2; i >= 0; --i)
	{
		int l = *pl;
		seamChain[i] = seamChain[i+1] + l;
		pl -= (width-l);
	}

	delete[] seamDisruption;
	delete[] link;

	return true;
}

