#include <Windows.h>
#include "IndicatorInterfaceUnit.h"
#include "TechnicalFunctions.h"

TIndexBuffer avg;

int period;

int hiPos, loPos, bars;

EXPORT void __stdcall Init()
{
	IndicatorShortName("My Moving Average");
	SetOutputWindow(ow_ChartWindow);
	SetEmptyValue(0.0);

	avg = CreateIndexBuffer();

	IndicatorBuffers(1);

	SetIndexBuffer(0, avg);
	SetIndexStyle(0, ds_Line, psSolid, 1, RGB(255, 0, 0));
	SetIndexLabel(0, "My MA");

	RegOption("Period", ot_Integer, &period);
	SetOptionRange("Period", 2, MaxInt);
	period = 5;
}

EXPORT void __stdcall OnParamsChage()
{
}

EXPORT void __stdcall Calculate(int index)
{
	if (index < period - 1){
		avg[index] = 0;
		return;
	}

	double sum = 0;
	for (int i = 0; i < period; i++){
		sum += Close(index + i);
	}
	avg[index] = sum / period;
}
