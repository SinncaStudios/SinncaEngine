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
	graphics* graphics::_instance = NULL;
	graphics* graphics::Instance()
	{
		if (_instance == NULL)
		{
			//_instance = new graphics;
			_instance = Heap->allocateNew<graphics>();
			
			//_instance->square = Heap->allocateNew<sprite>();
		}
		return _instance;
	}
	
	graphics::graphics()
	{
		fullScreen = false;
		
		//resW = glW;
		//resH = glH;
		
		
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
		printf("Maximum texture units supported: %i\n", (int)maxTextureUnits);
	}
	
	graphics::~graphics()
	{
		Heap->deallocateDelete(square);
	}
	
	void graphics::render()
	{
		/*
		 // reset frame
		 // draw scene
		 // draw gui
		 
		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		 //currentShader->bindShader();
		 
		 glMatrixMode(GL_MODELVIEW);
		 glLoadIdentity();
		 //scale(100.0f, 100.0f, 0.0f);
		 glScalef(100.0f, 100.0f, 0.0f);
		 glViewport(0, 0, resW, resH);
		 
		 //glUniformMatrix4fv(currentShader->uniformMVMatrix, 1, GL_FALSE, (float*)getModelMatrix());
		 
		 //square->render();
		 
		 //glEnableVertexAttribArray(currentShader->uniformMVMatrix);
		 //glVertexAttribPointer(currentShader->attributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
		 
		 //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		 
		 glLoadIdentity();
		 glEnable(GL_TEXTURE_2D);
		 glEnableClientState(GL_VERTEX_ARRAY);
		 glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		 
		 // disable scissor render
		 if (glIsEnabled(GL_SCISSOR_TEST))
		 {
		 glScissor(0, 0, resW, resH);
		 glDisable(GL_SCISSOR_TEST);
		 }
		 
		 //axisWidget(0.1f);
		 if (Tree->currentScene->pers() == 1)
		 {
		 Tree->currentScene->render();
		 }
		 
		 
		 glMatrixMode(GL_PROJECTION);
		 glPushMatrix();
		 glLoadIdentity();
		 
		 #ifdef sniPhone
		 //GLKMatrix4MakeOrtho(0, resW, 0, resH, 1, -1);
		 //GLKMatrix4MakeOrtho(0, 960, 0, 640, 1, -1);
		 glOrthof(0, resW, 0, resH, -1, 1);
		 //ortho(0, resW, 0, resH, -1.0, 1.0);
		 #else
		 gluOrtho2D(0, resW >> 1, resH >> 1, 0);
		 #endif
		 
		 glMatrixMode(GL_MODELVIEW);
		 glLoadIdentity();
		 
		 glDisable(GL_LIGHTING); // 2D elements are not effected by lighting
		 glDisable(GL_CULL_FACE); // all 2D elements are not to be culled
		 
		 
		 DefaultShader->bindShader();
		 if (Tree->currentScene->pers() == 0)
		 {
		 glPushMatrix();
		 //glScalef(0.5f, 0.5f, 0.0f);
		 //glTranslatef(500, 500, 0);
		 //Camera->look2D();
		 
		 Tree->currentScene->render();
		 
		 glPopMatrix();
		 }
		 
		 //Tree->currentScene->drawGui();
		 
		 
		 glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		 glDisableClientState(GL_VERTEX_ARRAY);
		 glEnable(GL_LIGHTING);
		 glEnable(GL_CULL_FACE); // turn these back on
		 
		 glMatrixMode(GL_PROJECTION);
		 glPopMatrix();
		 glMatrixMode(GL_MODELVIEW);
		 */
		// reset frame
		// draw scene
		// draw gui
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		TimeKeeper->update();
		/*
		 glLoadIdentity();
		 glEnable(GL_TEXTURE_2D);
		 glEnableClientState(GL_VERTEX_ARRAY);
		 glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		 
		 // disable scissor render
		 if (glIsEnabled(GL_SCISSOR_TEST))
		 {
		 glScissor(0, 0, resW, resH);
		 glDisable(GL_SCISSOR_TEST);
		 }
		 
		 //axisWidget(0.1f);
		 if (Tree->currentScene->pers() == 1)
		 {
		 Tree->currentScene->render();
		 }
		 
		 
		 glMatrixMode(GL_PROJECTION);
		 glPushMatrix();
		 glLoadIdentity();
		 #ifdef sniPhone
		 //GLKMatrix4MakeOrtho(0, resW, 0, resH, 1, -1);
		 //GLKMatrix4MakeOrtho(0, 960, 0, 640, 1, -1);
		 //glOrthof(0, resW, 0, resH, -1, 1);
		 glViewport(0, 0, resW, resH);
		 ortho(0, resW, 0, resH, -1.0, 1.0);
		 #else
		 gluOrtho2D(0, resW >> 1, resH >> 1, 0);
		 #endif
		 glMatrixMode(GL_MODELVIEW);
		 glLoadIdentity();
		 
		 glDisable(GL_LIGHTING); // 2D elements are not effected by lighting
		 glDisable(GL_CULL_FACE); // all 2D elements are not to be culled
		 */
		//static float left = 0.0f;
		
		setMatrixMode(SINNCA_MODELVIEW_MATRIX);
		loadIdentity();
		
		//DefaultShader->bindShader();
		currentShader->bindShader();
		if (Tree->currentScene->pers() == 0)
		{
			//glPushMatrix();
			//glScalef(0.5f, 0.5f, 0.0f);
			//glTranslatef(500, 500, 0);
			Camera->look2D();
			
			Tree->currentScene->render();
			
			//glPopMatrix();
		}
		
		//Tree->currentScene->drawGui();
		
		/*
		 glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		 glDisableClientState(GL_VERTEX_ARRAY);
		 glEnable(GL_LIGHTING);
		 glEnable(GL_CULL_FACE); // turn these back on
		 
		 glMatrixMode(GL_PROJECTION);
		 glPopMatrix();
		 glMatrixMode(GL_MODELVIEW);
		 */
		//left += 0.1f;
	}
	
	void graphics::init(unsigned int w, unsigned int h)
	{
		currentShader = DefaultShader;
		square = Heap->allocateNew<sprite>();
		
		// Initialization code here.
		glClearColor(0.1, 0.24, 0.4, 0);
		
		const unsigned char* temp = glGetString(GL_VENDOR);
		const unsigned char* temp2 = glGetString(GL_RENDERER);
		const unsigned char* temp3 = glGetString(GL_VERSION);
		printf("Graphics Card: %s\nRenderer: %s\nVersion: %s\n", temp, temp2, temp3);
		
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		
		setMatrixMode(SINNCA_PROJECTION_MATRIX);
		loadIdentity();
		
		ortho(-1.0f, 1.0f);
		
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		
		//move(-(resW * 0.5f), -(resH * 0.5f), 0.0f);
		
		/*
		 glDisable(GL_DEPTH_TEST);
		 glDepthMask(GL_FALSE);
		 
		 glEnable(GL_TEXTURE_2D);
		 
		 // enable alpha fuctions
		 
		 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		 glEnable(GL_BLEND);
		 
		 
		 glEnable(GL_CULL_FACE);
		 
		 glCullFace(GL_BACK);
		 
		 glEnable (GL_LIGHTING);
		 glEnable (GL_LIGHT0);
		 glShadeModel (GL_SMOOTH);
		 
		 glClearDepth(1.0);
		 glEnable(GL_DEPTH_TEST);
		 glDepthFunc(GL_LEQUAL);
		 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		 */
		
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
		
		
		//setMatrixMode(SINNCA_MODELVIEW_MATRIX);
		move(-half_width, -half_height, 0.0f);
		//move(-100.0f, 0.0f, 0.0f);
		
		
	}
	
	void graphics::sceneColor(float r, float g, float b)
	{
		glClearColor(r, g, b, 1.0f);
	}
	
	m4* graphics::getModelMatrix()
	{
		return &modelViewStack[modelViewIndex];
	}
	m4* graphics::getProjectionMatrix()
	{
		return &projectionStack[projectionIndex];
	}
	m4* graphics::getTextureMatrix()
	{
		return &textureStack[textureIndex];
	}
	m4* graphics::getCombinedMatrix()
	{
		multiply(&combinedModelProj, getProjectionMatrix(), getModelMatrix());
		return &combinedModelProj;
	}
	
	
	m3* graphics::getNormalMatrix()
	{
		m4 matrix;
		
		copyMatrix(&matrix, getModelMatrix());
		invert(&matrix);
		transpose(&matrix);
		
		copyMatrix(&normalMatrix, &matrix);
		return &normalMatrix;
	}
	
	
	void graphics::setScreenSize(int w, int h)
	{
		resH = h;
		resW = w;
	}
	
	void graphics::enableScissor(int x, int y, int w, int h)
	{
		if (glIsEnabled(GL_SCISSOR_TEST) == false)
		{
			glEnable(GL_SCISSOR_TEST);
		}
		glScissor(x, y, w, h);
	}
	
	void graphics::move(point p)
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
	
	void graphics::move(float x, float y, float z)
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
	
	void graphics::rotate(point p)
	{
		//glRotatef(1.0f, p.x, p.y, p.z);
	}
	
	void graphics::scale(point p)
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
	
	void graphics::scale(float x, float y, float z)
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
	
	void graphics::loadIdentity()
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
	
	void graphics::pushMatrix()
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
	
	void graphics::popMatrix()
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
	
	void graphics::ortho(float near, float far)
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
	
	void graphics::perspective(float end,  float start = 0.1f, float fov = 35.0f)
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
	
	void graphics::setMatrixMode(uint mode)
	{
		matrixMode = mode;
	}
}

