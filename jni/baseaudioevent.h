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
#ifndef __BASEAUDIOEVENT_H_INCLUDED__
#define __BASEAUDIOEVENT_H_INCLUDED__

#include "audiobuffer.h"

class BaseAudioEvent
{
    public:
        BaseAudioEvent();
        ~BaseAudioEvent();

        /**
         * an BaseAudioEvent contains a buffer holding the samples, this
         * is used by the AudioRenderer to write the events samples into the output buffer
         */
        virtual AudioBuffer* getBuffer();

        /**
         * an AudioEvent can also synthesize audio live, this
         * method should be called during the write cycle on
         * each buffer update of the AudioRenderer
         * @param aBufferLength {int} desired buffer length ( usually buffer size )
         * @return {AudioBuffer*} the buffer containing the live generated samples
         */
        virtual AudioBuffer* synthesize( int aBufferLength );

        virtual int getSampleLength();
        virtual int getSampleStart();
        virtual int getSampleEnd();

        virtual void setSampleLength( int value );
        virtual void setSampleStart( int value );
        virtual void setSampleEnd( int value );

        virtual bool deletable();   // query whether this event is queued for deletion
        virtual void setDeletable( bool value );

        virtual bool isEnabled();   // whether this audio event is elligible for playback
        virtual void setEnabled( bool value );

        virtual void lock();        // "lock" mutations within this events buffer during reading
        virtual void unlock();      // unlock
        virtual bool isLocked();

        virtual void destroy();

    protected:

        // buffer regions
        int _sampleStart;
        int _sampleEnd;
        int _sampleLength;

        bool _enabled;

        // cached buffer
        AudioBuffer* _buffer;
        void destroyBuffer();

        bool _deleteMe;
        bool _locked;
        bool _updateAfterUnlock;    // use in update-methods when checking for lock
};

#endif
