/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2013-2014 Igor Zinken - http://www.igorski.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "fm.h"
#include <math.h>
#include "utils.h"

// constructor

FrequencyModulator::FrequencyModulator( int aWaveForm, float aRate )
{
    _wave          = aWaveForm;
    _phase         = 0.0;
    _phaseIncr     = 0.0;
    _length        = 0;
    _buffer        = BufferUtil::generateSilentBuffer( BufferUtil::calculateBufferLength( MIN_LFO_RATE ));
    modulator      = 0.0;
    carrier        = 0.0;
    fmamp          = 10;
    AMP_MULTIPLIER = 0.15;
    TWO_PI         = 2 * ( atan( 1 ) * 4 );

    setRate( aRate );
}

/* public methods */

void FrequencyModulator::process( AudioBuffer* sampleBuffer, bool isMonoSource )
{
    int bufferSize = sampleBuffer->bufferSize;

    for ( int c = 0, ca = sampleBuffer->amountOfChannels; c < ca; ++c )
    {
        SAMPLE_TYPE* channelBuffer = sampleBuffer->getBufferForChannel( c );

        for ( int i = 0; i < bufferSize; ++i )
        {
            modulator = modulator + ( TWO_PI_OVER_SR * _rate );
            modulator = modulator < TWO_PI ? modulator : modulator - TWO_PI;

            carrier            = channelBuffer[ i ];
            channelBuffer[ i ] = ( carrier * cos( carrier + fmamp * cos( modulator )))/* * AMP_MULTIPLIER*/;
        }
        // save CPU cycles when source is mono
        if ( isMonoSource )
        {
            sampleBuffer->applyMonoSource();
            break;
        }
    }
}
