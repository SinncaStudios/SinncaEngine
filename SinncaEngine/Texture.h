//
//  Texture.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/3/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Texture__
#define __SinncaEngine__Texture__

#include <iostream>
#include "Color.h"
#include "Image.h"

namespace sinnca
{
	class texture : public color
	{
		image* source;
		
		// Offset in image atlas
		uint xOff, yOff;
		uint xSize, ySize;
		
	public:
		
		//std::string name;
		
		texture(std::string n);
		~texture();
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
		
		void setSource(image* i);
		image* getSource();
		void setOffset(uint x, uint y);
		void setSize(uint x, uint y);
		
		void getOffset(uint& x, uint& y);
		void getSize(uint& x, uint& y);
		void bind();
	};
	
	texture* checkTexture(int ind);
	
#define createTexture(a) new(a)texture(a)
	void registerTexture(lua_State* L);
}

#endif /* defined(__SinncaEngine__Texture__) */
