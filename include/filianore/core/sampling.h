#ifndef _SAMPLING_H
#define _SAMPLING_H

#include <algorithm>
#include "elemental.h"
#include "../ext/pcg32.h"

namespace filianore
{

    template <typename T>
    FILIANORE_INLINE void Shuffle(T *samp, int count, int nDimensions, pcg32 &pcg32)
    {
        for (int i = 0; i < count; ++i)
        {
            int other = i + pcg32.nextUInt(count - i);
            for (int j = 0; j < nDimensions; ++j)
            {
                std::swap(samp[nDimensions * i + j], samp[nDimensions * other + j]);
            }
        }
    }

} // namespace filianore

#endif