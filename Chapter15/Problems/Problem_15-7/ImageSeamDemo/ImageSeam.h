#ifndef _IMAGE_SEAM_H_
#define _IMAGE_SEAM_H_


class ImageSeam
{
public:
	ImageSeam();
	ImageSeam(int w, int h);
	~ImageSeam();

	bool SetSize(int w, int h);
	void Clear();
	void GenerateRandomDisruption();
	bool SetDisruption(int x, int y, unsigned char d);
	const int GetWidth() const { return width; }
	const int GetHeight() const { return height; }
	const unsigned char GetDisruption(int x, int y) const;
	const int GetTotalDisruption() const { return totalDisruption; }
	bool BuildImageSeam();

	const unsigned char* GetDisruptionBuffer() const { return disruption; }
	const int* GetSeamChainBuffer() const { return seamChain; }

	static const int DISRUPTION_MAX = 100;

private:
	int width;
	int height;
	unsigned char *disruption;
	int *seamChain;
	int totalDisruption;
};


#endif // #ifndef _IMAGE_SEAM_H_#pragma once
