#include "..\..\AASM6_Library\AASM6\AASM6.h"

void DemoFunc()
{
	float Res;
	AASM6::InputComplex x_1{ 0.0f, 0.0f }, x_2{ 0.0f, 0.0f };
	AASM6::get_Cyalf_ConCil(Res, 2, 2, 2, x_1, x_2);
	AASM6::get_Cyalf_OgiCil(Res, 2, 2, 2, x_1, x_2);
}