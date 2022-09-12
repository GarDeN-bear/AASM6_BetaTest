#include "Extensions.h"

float Linterp(vector<vector<float>>& XY, float x)
{
	if (x <= XY[0][0]) {
		return XY[0][1];
	}
	else if (x >= XY[XY.size() - 1][0]) {
		return XY[XY.size() - 1][1];
	}
	else {
		unsigned int i = 0;
		while (i < XY.size() - 1)
		{
			if (x >= XY[i][0] && x < XY[i + 1][0])
			{
				return XY[i][1] * ((XY[i + 1][0] - x) / (XY[i + 1][0] - XY[i][0])) + XY[i + 1][1] * (1 - (XY[i + 1][0] - x) / (XY[i + 1][0] - XY[i][0]));
			}
			i = i + 1;
		}
	}
}


float Linterp(const float XY[][2], unsigned int size, float x)
{
	if (x <= XY[0][0]) {
		return XY[0][1];
	}
	else if (x >= XY[size - 1][0]) {
		return XY[size - 1][1];
	}
	else {
		unsigned int i = 0;
		while (i < size - 1)
		{
			if (x >= XY[i][0] && x < XY[i + 1][0])
			{
				return XY[i][1] * ((XY[i + 1][0] - x) / (XY[i + 1][0] - XY[i][0])) + XY[i + 1][1] * (1 - (XY[i + 1][0] - x) / (XY[i + 1][0] - XY[i][0]));
			}
			i = i + 1;
		}
	}
	
	return NAN;
}

float sqr(float x)
{
	return x * x;
}


float LinterpOnce(float x1, float y1, float x2, float y2, float x)
{
	return y1 * ((x2 - x) / (x2 - x1)) + y2 * (1 - (x2 - x) / (x2 - x1));
}
