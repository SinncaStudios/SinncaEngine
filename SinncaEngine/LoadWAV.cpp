//
//  LoadWAV.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 10/16/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Buffer.h"
#include "Heap.h"

namespace sinnca
{
	struct riffChunk
	{
		char chunkId[4];
		long chunkSize;
		char format[4];
	};
	struct formatChunk
	{
		char chunkId[4];
		long chunkSize;
		short format;
		uint noOfChannels;
		long sampleRate;
		long byteRate;
		short align;
		short perSample;
		
	};
	
	struct wavChunk
	{
		char chunkId[4];
		long chunkSize;
	};
	
	int buffer::loadWAV(std::string path)
	{
		
		FILE* f = fopen(path.c_str(), "fb");
		
		riffChunk riff;
		formatChunk format;
		wavChunk wav;
		
		fread(&riff, sizeof(riffChunk), 1, f);
		
		if ((riff.chunkId[0] != 'R' ||
			 riff.chunkId[1] != 'I' ||
			 riff.chunkId[2] != 'F' ||
			 riff.chunkId[3] != 'F') ||
			(riff.format[0] != 'W' ||
			 riff.format[1] != 'A' ||
			 riff.format[2] != 'V' ||
			 riff.format[3] != 'E'))
		{
			printf("This file has an invalid Riff or Wave header.\n");
			return -1;
		}
		
		fread(&format, sizeof(formatChunk), 1, f);
		
		if (format.chunkId[0] != 'f' ||
			format.chunkId[1] != 'm' ||
			format.chunkId[2] != 't' ||
			format.chunkId[3] != ' ')
		{
			printf("This file has an invalid format.\n");
			return -1;
		}
		
		if (format.chunkSize > 16)
		{
			fseek(f, sizeof(short), SEEK_CUR);
		}
		
		fread(&wav, sizeof(wavChunk), 1, f);
		
		if (wav.chunkId[0] != 'd' ||
			wav.chunkId[1] != 'a' ||
			wav.chunkId[2] != 't' ||
			wav.chunkId[3] != 'a')
		{
			printf("Invalid data.\n");
		}
		
		unsigned char* toBuffer = (unsigned char*)Heap->allocate((ui32)wav.chunkSize, alignof(unsigned char*));
		if (!fread(toBuffer, wav.chunkSize, 1, f))
		{
			printf("Error reading wav data.\n");
			return -1;
		}
		
		if (format.noOfChannels == 1)
		{
			if (format.perSample == 8)
			{
				bufFormat = AL_FORMAT_MONO8;
				
			} else if (format.perSample == 16)
			{
				bufFormat = AL_FORMAT_MONO16;
			}
			
		} else if (format.noOfChannels == 2)
		{
			if (format.perSample == 8)
			{
				bufFormat = AL_FORMAT_STEREO8;
				
			} else if (format.perSample == 16)
			{
				bufFormat = AL_FORMAT_STEREO16;
			}
			
		}
		
		size = wav.chunkSize;
		frequency = format.sampleRate;
		
		alBufferData(theBuffer, bufFormat, (void*)toBuffer, size, frequency);
		
		fclose(f);
		return 0;
	}
}