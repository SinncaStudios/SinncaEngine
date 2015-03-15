//
//  Image.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/3/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Image__
#define __SinncaEngine__Image__

#include <iostream>
#include "Heap.h"
#include "Script.h"
#include "Asset.h"

#include "i_graphics.h"

namespace sinnca
{
	enum texBlend
	{
		smooth = GL_LINEAR,
		hard = GL_NEAREST
	};
	
	enum texWrap
	{
		repeat = GL_REPEAT,
		mirrored = GL_MIRRORED_REPEAT,
		clampEdge = GL_CLAMP_TO_EDGE
		//clampBorder = GL_CLAMP_TO_BORDER;
	};
	
	class image : public asset
	{
		GLuint data, colorType;
		
		int w, h, bitDepth;
		
		int loadPNG(std::string path);
		int loadJPG(std::string path);
		int loadGIF(std::string path);
		int loadTGA(std::string path);
		int loadBMP(std::string path);
		int loadPSD(std::string path);
		int loadXCF(std::string path);
		int loadPSP(std::string path);
		int loadSNI(std::string path);
		int loadTIFF(std::string path);
		
	public:
		
		static constexpr auto metatable = "image";
		
		bool bound;
		std::string name, path;
		texBlend tb;
		
		image(std::string n);
		~image();
		
		void bind();
		void load(std::string p);
		GLuint getData();
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
		
		
	};
	
#define createImage(a) new(a)image(a)
	
	void registerImage(lua_State* L);
	
}

#endif /* defined(__SinncaEngine__Image__) */
