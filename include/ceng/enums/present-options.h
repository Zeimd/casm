/*****************************************************************************
*
* present-options.h
*
* Created By Jari Korkala 3/3/2015
*
*****************************************************************************/

#ifndef CENG_PRESENT_OPTIONS_H
#define CENG_PRESENT_OPTIONS_H

namespace Ceng
{
	namespace PresentOptions
	{
		enum value
		{
			// Use v-sync instead of instead of buffer sequence
			do_not_sequence = 1 ,

			// Call to Present fails if still drawing previous frame
			do_not_wait = 1 << 1 ,

			// Determine when to exit idle state
			present_test = 1 << 2 ,

			// Discard queued present calls
			restart = 1 << 3 ,

			// Don't allow redirection to another output.
			restrict_to_output = 1 << 4 ,

			// If stereo image must be converted to mono, prefer
			// right channel instead of left.
			stereo_prefer_right = 1 << 5 ,

			// Use left channel as mono buffer for this frame.
			stereo_temporary_mono = 1 << 6 ,

			// Use custom refresh rate
			use_duration = 1 << 7 ,

			force32b = 1 << 30 ,
		};
	}
}

#endif