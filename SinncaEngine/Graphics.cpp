//
//  Graphics.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/1/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Graphics.h"
#include "Heap.h"
#include "Computer.h"
#include "Platform.h"
#include "TimeKeeping.h"

#include "i_graphics.h"
#include <math.h>

#include "Global.h"

#include "Tree.h"
#include "Camera.h"

namespace sinnca
{
	
	namespace Graphics
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
		
		//camera mainCamera;
		
		// OpenGL information
		GLint maxTextureUnits;
		
		
		sprite* square;
		
		shader* defaultShader;
		shader* currentShader;
		image* currentImage;
		
		
		
		void shutdown()
		{
			Heap->deallocateDelete(square);
		}
		
		void render()
		{
			// reset frame
			// draw scene
			// draw gui
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			TimeKeeper::update();
			
			
			setMatrixMode(SINNCA_MODELVIEW_MATRIX);
			loadIdentity();
			
			
			currentShader->bindShader();
			if (Tree::currentScene->pers() == 0)
			{
				
				Tree::currentScene->mainCamera.look2D();
				
				Tree::currentScene->render();
				
			}
		}
		
		void init(unsigned int w, unsigned int h)
		{
			
			fullScreen = false;
			
			defaultShader = createShader("defaultShader");
			defaultShader->loadShaders(Computer::getResourcePath() + "/BasicVert.vs", Computer::getResourcePath() + "/BasicFrag.fs");
			defaultShader->initShaders();
			
			currentShader = defaultShader;
			square = Heap->allocateNew<sprite>();
			
			// Initialization code here.
			glClearColor(0.1, 0.24, 0.4, 0);
			
			// basic OpenGL info
			const unsigned char* temp = glGetString(GL_VENDOR);
			const unsigned char* temp2 = glGetString(GL_RENDERER);
			const unsigned char* temp3 = glGetString(GL_VERSION);
			printf("Graphics Card: %s\nRenderer: %s\nVersion: %s\n", temp, temp2, temp3);
			
			// get texture unit info
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB, &maxTextureUnits);
			printf("Maximum texture units supported: %i\n", (int)maxTextureUnits);
			
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			
			
			setMatrixMode(SINNCA_PROJECTION_MATRIX);
			loadIdentity();
			
			ortho(-1.0f, 1.0f);
			
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			
			
			setMatrixMode(SINNCA_TEXTURE_MATRIX);
			loadIdentity();
			
			setMatrixMode(SINNCA_PROJECTION_MATRIX);
			loadIdentity();
			
			setMatrixMode(SINNCA_MODELVIEW_MATRIX);
			loadIdentity();
			
			
			
#if sniPhone
			// for some reason it's reversed on the iPhone
			resH = w;
			resW = h;
#else
			resW = w;
			resH = h;
#endif
			
			float half_width  = ( float )resW * 0.5f,
			half_height = ( float )resH * 0.5f;
			
			glViewport(0, 0, resW, resH);
			setMatrixMode(SINNCA_PROJECTION_MATRIX);
			loadIdentity();
			ortho(-1.0f, 1.0f);
			
			
			move(-half_width, -half_height, 0.0f);
			
		}
		
		void sceneColor(float r, float g, float b)
		{
			glClearColor(r, g, b, 1.0f);
		}
		
		m4* getModelMatrix()
		{
			return &modelViewStack[modelViewIndex];
		}
		m4* getProjectionMatrix()
		{
			return &projectionStack[projectionIndex];
		}
		m4* getTextureMatrix()
		{
			return &textureStack[textureIndex];
		}
		m4* getCombinedMatrix()
		{
			multiply(&combinedModelProj, getProjectionMatrix(), getModelMatrix());
			return &combinedModelProj;
		}
		
		
		m3* getNormalMatrix()
		{
			m4 matrix;
			
			copyMatrix(&matrix, getModelMatrix());
			invert(&matrix);
			transpose(&matrix);
			
			copyMatrix(&normalMatrix, &matrix);
			return &normalMatrix;
		}
		
		
		void setScreenSize(int w, int h)
		{
			resH = h;
			resW = w;
		}
		
		void enableScissor(int x, int y, int w, int h)
		{
			if (glIsEnabled(GL_SCISSOR_TEST) == false)
			{
				glEnable(GL_SCISSOR_TEST);
			}
			glScissor(x, y, w, h);
		}
		
		void move(point p)
		{
			//glTranslatef(p.x, p.y, p.z);
			v3 vec = {p.x, p.y, p.z};
			
			switch (matrixMode)
			{
				case SINNCA_MODELVIEW_MATRIX:
				{
					snTranslateM4(getModelMatrix(), getModelMatrix(), &vec);
					break;
					
				}
				case SINNCA_PROJECTION_MATRIX:
				{
					snTranslateM4(getProjectionMatrix(), getProjectionMatrix(), &vec);
					break;
				}
				case SINNCA_TEXTURE_MATRIX:
				{
					snTranslateM4(getTextureMatrix(), getTextureMatrix(), &vec);
					break;
				}
			}
		}
		
		void move(float x, float y, float z)
		{
			//glTranslatef(x, y, z);
			v3 vec = {x, y, z};
			
			switch (matrixMode)
			{
				case SINNCA_MODELVIEW_MATRIX:
				{
					snTranslateM4(getModelMatrix(), getModelMatrix(), &vec);
					break;
					
				}
				case SINNCA_PROJECTION_MATRIX:
				{
					snTranslateM4(getProjectionMatrix(), getProjectionMatrix(), &vec);
					break;
				}
				case SINNCA_TEXTURE_MATRIX:
				{
					snTranslateM4(getTextureMatrix(), getTextureMatrix(), &vec);
					break;
				}
			}
		}
		
		void rotate(point p)
		{
			//glRotatef(1.0f, p.x, p.y, p.z);
		}
		
		void scale(point p)
		{
			//glScalef(p.x, p.y, p.z);
			v3 vec = {p.x, p.y, p.z};
			
			switch (matrixMode)
			{
				case SINNCA_MODELVIEW_MATRIX:
				{
					snScaleM4(getModelMatrix(), getModelMatrix(), &vec);
					break;
					
				}
				case SINNCA_PROJECTION_MATRIX:
				{
					snScaleM4(getProjectionMatrix(), getProjectionMatrix(), &vec);
					break;
				}
				case SINNCA_TEXTURE_MATRIX:
				{
					snScaleM4(getTextureMatrix(), getTextureMatrix(), &vec);
					break;
				}
			}
		}
		
		void scale(float x, float y, float z)
		{
			v3 vec = {x, y, z};
			
			switch (matrixMode)
			{
				case SINNCA_MODELVIEW_MATRIX:
				{
					snScaleM4(getModelMatrix(), getModelMatrix(), &vec);
					break;
					
				}
				case SINNCA_PROJECTION_MATRIX:
				{
					snScaleM4(getProjectionMatrix(), getProjectionMatrix(), &vec);
					break;
				}
				case SINNCA_TEXTURE_MATRIX:
				{
					snScaleM4(getTextureMatrix(), getTextureMatrix(), &vec);
					break;
				}
			}
		}
		
		void loadIdentity()
		{
			switch (matrixMode)
			{
				case SINNCA_MODELVIEW_MATRIX:
				{
					snLoadIdentity(getModelMatrix());
					break;
					
				}
				case SINNCA_PROJECTION_MATRIX:
				{
					snLoadIdentity(getProjectionMatrix());
					break;
				}
				case SINNCA_TEXTURE_MATRIX:
				{
					snLoadIdentity(getTextureMatrix());
					break;
				}
			}
		}
		
		void pushMatrix()
		{
			switch (matrixMode)
			{
				case SINNCA_MODELVIEW_MATRIX:
				{
					copyMatrix(&modelViewStack[modelViewIndex+1], &modelViewStack[modelViewIndex]);
					
					++modelViewIndex;
					break;
					
				}
				case SINNCA_PROJECTION_MATRIX:
				{
					copyMatrix(&projectionStack[projectionIndex+1], &projectionStack[projectionIndex]);
					
					++projectionIndex;
					break;
				}
				case SINNCA_TEXTURE_MATRIX:
				{
					copyMatrix(&textureStack[textureIndex+1], &textureStack[textureIndex]);
					
					++textureIndex;
					break;
				}
			}
		}
		
		void popMatrix()
		{
			switch (matrixMode)
			{
				case SINNCA_MODELVIEW_MATRIX:
				{
					--modelViewIndex;
					break;
					
				}
				case SINNCA_PROJECTION_MATRIX:
				{
					--projectionIndex;
					break;
				}
				case SINNCA_TEXTURE_MATRIX:
				{
					--textureIndex;
					break;
				}
			}
		}
		
		void ortho(float near, float far)
		{
			float left = (float)resW * 0.5f;
			float right = -(float)resW * 0.5f;
			float up = (float)resH * 0.5f;
			float down = -(float)resH * 0.5f;
			
			switch (matrixMode)
			{
				case SINNCA_MODELVIEW_MATRIX:
				{
					snOrthoMatrix(getModelMatrix(), left, right, up, down, near, far);
					break;
					
				}
				case SINNCA_PROJECTION_MATRIX:
				{
					snOrthoMatrix(getProjectionMatrix(), left, right, up, down, near, far);
					break;
				}
				case SINNCA_TEXTURE_MATRIX:
				{
					snOrthoMatrix(getTextureMatrix(), left, right, up, down, near, far);
					break;
				}
			}
		}
		
		void perspective(float end,  float start = 0.1f, float fov = 35.0f)
		{
			m4 base;
			float aspectRatio = (float)resW / (float)resH;
			
			float d = end - start,
			r = (fov * 0.5) * (M_PI / 180),
			s = sin(r),
			c = sin(r) / s;
			
			snLoadIdentity(&base);
			
			base.m[0].x = c / aspectRatio;
			base.m[1].y = c;
			base.m[2].z = -(end + start) / d;
			base.m[2].w = -1.0f;
			base.m[3].z = -2.0f * start * end / d;
			base.m[3].w = 0.0f;
			
			switch (matrixMode)
			{
				case SINNCA_MODELVIEW_MATRIX:
				{
					multiply(getModelMatrix(), getModelMatrix(), &base);
					break;
					
				}
				case SINNCA_PROJECTION_MATRIX:
				{
					multiply(getProjectionMatrix(), getProjectionMatrix(), &base);
					break;
				}
				case SINNCA_TEXTURE_MATRIX:
				{
					multiply(getTextureMatrix(), getTextureMatrix(), &base);
					break;
				}
			}
			
		}
		
		void setMatrixMode(uint mode)
		{
			matrixMode = mode;
		}
	}
	
}

