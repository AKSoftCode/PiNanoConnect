#pragma once

namespace Controller
{
	namespace Settings
	{
		struct MinMaxVal
		{
			double Min;
			double Max;

			bool isLessThan(double src, double target)
			{
				return src < target;
			}

			bool isGreaterThan(double src, double target)
			{
				return src > target;
			}

			bool IsInRangeMinMax(double x)
			{
                return (Min < x && x < Max);
			}
		};

		struct PIDVal
		{
			double P;
			double I;
			double D;
		};

		struct ADCConfig
		{
			double minRange;
			double maxRange;
			int countStart;
			int countEnd;
		};
	}
}
