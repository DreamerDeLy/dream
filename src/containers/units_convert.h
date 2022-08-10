/* 
================================================================================
 Units converter class.
--------------------------------------------------------------------------------
 Copyright © 2019-2021 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#pragma once 

#include "data.h"

namespace dream
{
	class UnitsConvert
	{
	private:
		const Value *v;

		//--------------------------------------------------------------------------
		// Get molecular weight of specific gas
		// Table from https://teesing.com/en/library/tools/ppm-mg3-converter
		//--------------------------------------------------------------------------
		static float getMolecularWeight(const String &gas)
		{
			// Data pair
			struct MW {
				const String gas;
				const float molecularWeight;
			};

			// Data table
			static const MW data[] = {
				{ "nh3", 	17.03f },
				{ "co", 	28.01f },
				{ "co2", 	44.01f },
				{ "cl2", 	70.9f },
				{ "ch2o", 	30.026f },
				{ "h2", 	2.02f },
				{ "ch4", 	16.04f },
				{ "h2s", 	34.08f },
				{ "no2", 	46.01f },
				{ "o3", 	48.00f },
				{ "c2cl4", 	165.822f },
				{ "so2", 	64.06f },
				{ "voc", 	78.9516f }
			};

			float molecularWeight = NULL_FLOAT;

			// Find MW for this gas
			for(const auto &mw : data)
			{
				if (mw.gas == gas) molecularWeight = mw.molecularWeight;
			}

			return molecularWeight;
		}

		//--------------------------------------------------------------------------
		// Convert mg/m3 to ppb for specific gas
		//--------------------------------------------------------------------------
		static float mgm3_to_ppb(const float val, const String &gas)
		{
			// Get molecular weight
			const float molecularWeight = getMolecularWeight(gas);

			// If molecular weight not found
			if (molecularWeight == NULL_FLOAT) return NULL_FLOAT;

			// Calculate result using formula
			// concentration (ppm) = 24.45 x concentration (mg/m3) ÷ molecular weight
			return (24.45f * val / molecularWeight) * 1000.0f;
		}

		//--------------------------------------------------------------------------
		// Convert ppb to mg/m3 for specific gas
		//--------------------------------------------------------------------------
		static float ppb_to_mgm3(const float val, const String &gas)
		{
			// Get molecular weight
			const float molecularWeight = getMolecularWeight(gas);

			// If molecular weight not found
			if (molecularWeight == NULL_FLOAT) return NULL_FLOAT;

			// Calculate result using formula
			// concentration (mg/m3) = 0.0409 x concentration (ppm) x molecular weight
			return (0.0409f * (val / 1000.0f) * molecularWeight);
		}

	public:
		UnitsConvert(const Value *value) : v(value) { }

		float toPPB()
		{
			if (v->unit == "ppb")
			{
				return v->asFloat();
			}
			else if (v->unit == "ppm")
			{
				return v->asFloat() * 1000.0f;
			}
			else if (v->unit == "ug/m3")
			{
				return mgm3_to_ppb(v->asFloat() / 1000, v->type);
			}

			return NULL_FLOAT;
		}

		float toPPM()
		{
			float ppb = toPPB();
			return (ppb != NULL_FLOAT ? ppb / 1000 : NULL_FLOAT);
		}

		float toMGM3()
		{
			if (v->unit == "ppb")
			{
				return ppb_to_mgm3(v->asFloat(), v->type);
			}
			else if (v->unit == "ppm")
			{
				return ppb_to_mgm3(v->asFloat() * 1000.0f, v->type);
			}
			else if (v->unit == "ug/m3")
			{
				return v->asFloat() / 1000;
			}

			return NULL_FLOAT;
		}

		float toUGM3()
		{
			float mgm3 = toMGM3();
			return (mgm3 != NULL_FLOAT ? mgm3 * 1000 : NULL_FLOAT);
		}
	};
}

