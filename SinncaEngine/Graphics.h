//
//  Graphics.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/1/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Graphics__
#define __SinncaEngine__Graphics__

#include <iostream>
#include "Types.h"
#include "Sprite.h"
#include "Shader.h"
#include "Matrix.h"
#include "Image.h"


namespace sinnca
{
	enum
	{
		SINNCA_MODELVIEW_MATRIX = 0,
		SINNCA_PROJECTION_MATRIX = 1,
		SINNCA_TEXTURE_MATRIX = 2
	};
	
#define Graphics (graphics::Instance())
	class graphics
	{
		
		int resW, resH;
		bool fullScreen;
		
		// the matrix variables
		raw matrixMode;
		raw modelViewIndex;
		raw projectionIndex;
		raw textureIndex;
		
		m4 modelViewStack[32];
		m4 projectionStack[2];
		m4 textureStack[2];
		m4 combinedModelProj;
		
		m3 normalMatrix;
		
		// OpenGL information
		GLint maxTextureUnits;
		
		
	public:
		
		static graphics* Instance();
		sprite* square;
		
		shader* currentShader;
		image* currentImage;
		
		graphics();
		~graphics();
		
		void render();
		
		void init(unsigned int w, unsigned int h);
		void setScreenSize(int w, int h);
		void enableScissor(int x, int y, int w, int h);
		void sceneColor(float r, float g, float b);
		
		void move(point p);
		void move(float x, float y, float z);
		void rotate(point p);
		void rotate(float x, float y, float z);
		void scale(point p);
		void scale(float x, float y, float z);
		void loadIdentity();
		void pushMatrix();
		void popMatrix();
		
		void ortho(float near, float far);
		void perspective(float end, float start, float fov);
		void setMatrixMode(uint mode);
		
		m4* getModelMatrix();
		m4* getProjectionMatrix();
		m4* getTextureMatrix();
		m4* getCombinedMatrix();
		
		m3* getNormalMatrix();
		
	protected:
		
		static graphics* _instance;
		
	};
}

#endif /* defined(__SinncaEngine__Graphics__) */
