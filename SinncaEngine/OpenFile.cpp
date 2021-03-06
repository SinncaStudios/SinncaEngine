//
//  OpenFile.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "OpenFile.h"

namespace sinnca
{
	
	char* openTextFile(std::string fileName)
	{
		char* text;
		
		if (!fileName.empty()) {
			FILE *file = fopen(fileName.c_str(), "rt");
			
			if (file != NULL) {
				fseek(file, 0, SEEK_END);
				int count = ftell(file);
				rewind(file);
				
				if (count > 0) {
					text = (char*)malloc(sizeof(char) * (count + 1));
					count = fread(text, sizeof(char), count, file);
					text[count] = '\0';
				}
				fclose(file);
			}
		}
		return text;
	}
}