//
//  Scene.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Scene.h"
#include "Graphics.h"
#include "MemoryManager.h"
#include "Palette.h"
#include "Tree.h"

#include <fstream>
#include "zlib.h"
#include "Utility.h"
#include "Engine.h"



namespace sinnca
{
	scene::scene() :
	alloced(false),
	perspective(0), // 2D by defualt
	percLoaded(0.0f)
	{
		col = &Palette::defaultColor;
		guiManager = createGuiMenu("mainMenu");
	}
	
	scene::~scene()
	{
		if (alloced) {
			assets.shutDown();
		}
		
	}
	
	void scene::onLoad()
	{
		switch (perspective)
		{
			case 0:
				Graphics::ortho(-1.0f, 1.0f);
				break;
				
			case 1:
				Graphics::perspective(100.f, 0.1f, 35.0f);
				break;
			default:
				break;
		}
	}
	void scene::unLoad()
	{
		
	}
	
	void scene::update()
	{
		
		for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->update();
		}
	}
	
	void scene::render()
	{
		Graphics::sceneColor(col->toFloat(col->r), col->toFloat(col->g), col->toFloat(col->b));
		
		for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->render();
		}
	}
	
	int scene::pers()
	{
		return perspective;
	}
	
	void* scene::operator new(size_t s, std::string n)
	{
		
		scene* sn = Script::createObject<scene>(Tree::sceneStorage);
		Script::setGlobal(n);
		return ((void*)sn);
	}
	
	void scene::operator delete(void *p)
	{
		
		Tree::sceneStorage->deallocate(p);
	}
	/*
	int scene::dumpToFile(std::string file)
	{
		
		std::string wFileExt = file;
		wFileExt.append(".sinncascene");
		std::ofstream f;
		f.open(wFileExt, std::ios::trunc | std::ios::binary | std::ios::out);
		if (!f.good())
		{
			printf("The file '%s' was not good", wFileExt.c_str());
			return -1;
		
		} else if (!f.is_open())
		{
			printf("The file '%s' could not be opened", wFileExt.c_str());
			return -1;
		}
		
		// set header
		// 8 bytes
		ui8* header = (ui8*)"sinnca_";
		f.write((char*)header, 8);
		// 2 bytes
		ui16 secondaryHeader = 18420;
		f.write((char*)&secondaryHeader, 2);
		
		// write engine version
		f.write((char*)&snEngineVersion, ARRAYSIZE(snEngineVersion));
		// write this file's version
		f.write((char*)&snFileVersion, ARRAYSIZE(snFileVersion));
		
		// write how many there are of things
		// images
		ui32 numberOfObjects = (ui32)assets.imageRef.size();
		f.write((char*)&numberOfObjects, 4);
		// textures
		numberOfObjects = (ui32)assets.textureRef.size();
		f.write((char*)&numberOfObjects, 4);
		// entities
		numberOfObjects = (ui32)assets.entityRef.size();
		f.write((char*)&numberOfObjects, 4);
		// grids
		numberOfObjects = (ui32)assets.gridRef.size();
		f.write((char*)&numberOfObjects, 4);
		// that's all that this version of the format can support
		
		
		for (ui32 i = 0; i < assets.imageRef.size(); i++)
		{
			// what kind of asset is this? (2 bytes)
			ui16 typeOfThing = 1;
			f.write((char*)&typeOfThing, 2); // 1 = image
			
			// what number asset are we at? (2 bytes)
			f.write((const char*) &i, 2);
			
			// what is the size of this asset? (2 bytes)
			ui16 sizeofthing = (sizeof(ui16) * 2) + ((image*)assets.imageRef[i])->name.length() + ((image*)assets.imageRef[i])->path.length() + 1;
			f.write((const char*)&sizeofthing, 2);
			// this is for just in case the engine doesn't support this type of object yet
			
			// write length of name
			ui16 sizeOfName = ((image*)assets.imageRef[i])->name.length();
			f.write((char*)&sizeOfName, 2);
			// then the name
			f << ((image*)assets.imageRef[i])->name.c_str();
			
			// write length of path to file
			sizeOfName = ((image*)assets.imageRef[i])->path.length();
			//then the path
			f << ((image*)assets.imageRef[i])->path;
			
			// finish off with the texture blend mode
			f.write((char*)&((image*)assets.imageRef[i])->tb, 1);
			
		}
		
		for (ui32 i = 0; i < assets.textureRef.size(); i++)
		{
			// what kind of asset is this? (2 bytes)
			ui16 typeOfThing = 2;
			f.write((char*)&typeOfThing, 2); // 2 = texture
			
			// what number asset are we at? (2 bytes)
			f.write((const char*) &i, 2);
			
			// what is the size of this asset? (2 bytes)
			ui16 sizeofthing = sizeof(ui16) + ((texture*)assets.textureRef[i])->name.length();
			f.write((const char*)&sizeofthing, 2);
			// this is for just in case the engine doesn't support this type of object yet
			
			
			// write length of name
			ui16 sizeOfName = ((texture*)assets.textureRef[i])->name.length();
			f.write((char*)&sizeOfName, 2);
			// then the name
			f << ((texture*)assets.textureRef[i])->name.c_str();
			
			// get the offset and size
			static ui32 tempx, tempy;
			((texture*)assets.textureRef[i])->getOffset(tempx, tempy);
			f.write((char*)&tempx, 4);
			f.write((char*)&tempy, 4);
			
			((texture*)assets.textureRef[i])->getSize(tempx, tempy);
			f.write((char*)&tempx, 4);
			f.write((char*)&tempy, 4);
			
			// write the link to the image source
			if (assets.imageRef.size() == 0)
			{
				i32 useDefault = -1;
				f.write((char*)&useDefault, 4);
				
			} else {
				for (ui32 j = 0; j < assets.imageRef.size(); j++)
				{
					if ((image*)assets.imageRef[j] == ((texture*)assets.textureRef[i])->getSource())
					{
						f.write((char*)&j, 4);
					}
				}
			}
			
			// This space reserved for color overlay mode
			// currently the color mode is: multiply. This means that the pixels in the texture will be multiplied by the base color and the product can only be darker then the original texture
			typeOfThing = 0;
			f.write((char*)&typeOfThing, 2);
			// write 0 for now
			
			// write the base color
			f.write((const char*)&((texture*)assets.textureRef[i])->r, 1);
			f.write((const char*)&((texture*)assets.textureRef[i])->g, 1);
			f.write((const char*)&((texture*)assets.textureRef[i])->b, 1);
			f.write((const char*)&((texture*)assets.textureRef[i])->a, 1);
			
		}
		
		for (ui32 i = 0; i < assets.entityRef.size(); i++)
		{
			// what kind of node is this? (2 bytes)
			ui16 typeOfThing = 1;
			f.write((char*)&typeOfThing, 2); // 1 = entity
			
			// what number node are we at? (2 bytes)
			f.write((const char*) &i, 2);
			
			// what is the size of this node (2 bytes)
			ui16 sizeofthing = sizeof(ui16) + ((entity*)assets.entityRef[i])->name.length();
			f.write((const char*)&sizeofthing, 2);
			// this is for just in case the engine doesn't support this type of object yet
			
			
			// write length of name
			ui16 sizeOfName = ((entity*)assets.entityRef[i])->name.length();
			f.write((char*)&sizeOfName, 2);
			// then the name
			f << ((entity*)assets.entityRef[i])->name.c_str();
			
			// will it draw?
			f.write((char*)&((entity*)assets.entityRef[i])->draw, 1);
			
			//Link to render object
			ui32 renderLink = -1;
			f.write((char*)&renderLink, 4);
			
			// Link to color
			ui32 colorLink = -1;
			for (ui32 j = 0; j < colorRef.size(); j++)
			{
				if (entityRef[i]->col == colorRef[j])
				{
					f.write((char*)&j, 4);
					break;
					
				} else if ((j + 1) >= colorRef.size())
				{
					// we've reached the end without a match
					f.write((char*)&colorLink, 4);
				}
			}
			
			// entity position
			f.write((const char*) &entityRef[i]->pos.x, sizeof(float));
			f.write((const char*) &entityRef[i]->pos.y, sizeof(float));
			f.write((const char*) &entityRef[i]->pos.z, sizeof(float));
			
			// entity rotation
			f.write((const char*) &entityRef[i]->rot.x, sizeof(float));
			f.write((const char*) &entityRef[i]->rot.y, sizeof(float));
			f.write((const char*) &entityRef[i]->rot.z, sizeof(float));
			
			// entity scale
			f.write((const char*) &entityRef[i]->scl.x, sizeof(float));
			f.write((const char*) &entityRef[i]->scl.y, sizeof(float));
			f.write((const char*) &entityRef[i]->scl.z, sizeof(float));
			
			// Link to parent node
			ui32 nodeLink = -1;
			for (ui32 j = 0; j < nodeRef.size(); j++)
			{
				if (entityRef[i]->parent == nodeRef[j])
				{
					f.write((char*)&j, 4);
					break;
					
				} else if ((j + 1) >= nodeRef.size())
				{
					// we've reached the end without a match
					f.write((char*)&nodeLink, 4);
				}
			}
			
		}
		
		for (ui32 i = 0; i < gridRef.size(); i++)
		{
			// what kind of node is this? (2 bytes)
			ui16 typeOfThing = 2;
			f.write((char*)&typeOfThing, 2); // 2 = grid
			
			// what number node are we at? (2 bytes)
			f.write((const char*) &i, 2);
			
			// what is the size of this node (2 bytes)
			ui16 sizeofthing = sizeof(ui16) + entityRef[i]->name.length();
			f.write((const char*)&sizeofthing, 2);
			// this is for just in case the engine doesn't support this type of object yet
			
			
			// write length of name
			ui16 sizeOfName = gridRef[i]->name.length();
			f.write((char*)&sizeOfName, 2);
			// then the name
			f << gridRef[i]->name.c_str();
			
			// will it draw?
			f.write((char*)&gridRef[i]->draw, 1);
			
			// is it isometric?
			f.write((char*)&gridRef[i]->iso, 1);
			
			//Link to render object
			ui32 renderLink = -1;
			f.write((char*)&renderLink, 4);
			
			// write grid size
			ui16 tempint = gridRef[i]->getX();
			f.write(reinterpret_cast<const char*>(&tempint), 2);
			tempint = gridRef[i]->getY();
			f.write(reinterpret_cast<const char*>(&tempint), 2);
			
			// go through the attributes of the tiles
			for (int j = 0; j < gridRef[i]->getX(); j++)
			{
				for (int k = 0; k < gridRef[i]->getY(); k++)
				{
					static bool tempbool = gridRef[i]->getTile(j, k)->getSolid();
					f.write((const char*) &tempbool, 1);
					
					for (int l = 0; l < textureRef.size(); l++)
					{
						if (gridRef[i]->getTile(j, k)->getTex() == textureRef[l])
						{
							f.write((const char*) &l, 2);
							break;
							// loop-ception!
						}
					}
				}
			}
			
			// grid position
			f.write((const char*) &gridRef[i]->pos.x, 4);
			f.write((const char*) &gridRef[i]->pos.y, 4);
			f.write((const char*) &gridRef[i]->pos.z, 4);
			
			// grid rotation
			f.write((const char*) &gridRef[i]->rot.x, 4);
			f.write((const char*) &gridRef[i]->rot.y, 4);
			f.write((const char*) &gridRef[i]->rot.z, 4);
			
			// grid scale
			f.write((const char*) &gridRef[i]->scl.x, 4);
			f.write((const char*) &gridRef[i]->scl.y, 4);
			f.write((const char*) &gridRef[i]->scl.z, 4);
			
			// Link to parent node
			ui32 nodeLink = -1;
			for (ui32 j = 0; j < nodeRef.size(); j++)
			{
				if (entityRef[i]->parent == nodeRef[j])
				{
					f.write((char*)&j, 4);
					break;
					
				} else if ((j + 1) >= nodeRef.size())
				{
					// we've reached the end without a match
					f.write((char*)&nodeLink, 4);
				}
			}
		}
		
		f.close();
		return 0;
	}
	
	int scene::readFromFile(std::string file)
	{
		std::string wFileExt = file;
		if (!wFileExt.find_last_of("."))
		{
			// no file extention. put one on
			wFileExt.append(".sinncascene");
		}
		
		std::ifstream f(wFileExt, std::ios::binary);
		if (!f.good())
		{
			printf("File stream is not good.");
			return -1;
			
		} else if (!f.is_open())
		{
			printf("Could not open %s", wFileExt.c_str());
			return -1;
		}
		
		
		char buffer[8];
		ui16 secondaryHeader = 0;
		f.read(buffer, 8);
		f.read((char*)&secondaryHeader, 2);
		
		if (!strcmp(buffer, "sinnca_") && secondaryHeader != 18420)
		{
			f.close();
			printf("This is not a valid sinnca scene file");
			return -1;
		}
		
		// Get the engine and file version that wrote this file
		ui8 eVersion[3];
		ui8 fVersion[3];
		f.read((char*)&eVersion[0], 1);
		f.read((char*)&eVersion[1], 1);
		f.read((char*)&eVersion[2], 1);
		
		f.read((char*)&fVersion[0], 1);
		f.read((char*)&fVersion[1], 1);
		f.read((char*)&fVersion[2], 1);
		
		if ((eVersion[0] > snEngineVersion[0]) ||
			(eVersion[1] > snEngineVersion[1]) ||
			(eVersion[2] > snEngineVersion[2]) ||
			(fVersion[0] > snFileVersion[0]) ||
			(fVersion[1] > snFileVersion[1]) ||
			(fVersion[2] > snFileVersion[2]))
		{
			printf("File: %s wa created by a later engine version, some objects may not be loaded.\n", wFileExt.c_str());
		}
		
		// how many of everything is there?
		ui32 noOfImages;
		f.read((char*)&noOfImages, 4);
		ui32 noOfTextures;
		f.read((char*)&noOfTextures, 4);
		ui32 noOfEntities;
		f.read((char*)&noOfEntities, 4);
		ui32 noOfGrids;
		f.read((char*)&noOfGrids, 4);
		
		// create containers
		image* imageContainer = (image*)memoryManager->allocate(sizeof(image*) * noOfImages);
		texture* textureContainer = (texture*)memoryManager->allocate(sizeof(texture*) * noOfTextures);
		node* nodeContainer = (node*)memoryManager->allocate(sizeof(node*) * (noOfEntities + noOfGrids));
		
		
		// read the images
		for (ui32 i = 0; i < noOfImages; i++)
		{
			// read type
			ui16 typeOfThing;
			f.read((char*)&typeOfThing, 2);
			
			// position in container
			ui32 entryPosition;
			f.read((char*)&entryPosition, 4);
			
			// size of object
			ui16 sizeOfThing;
			f.read((char*)&sizeOfThing, 2);
			
			// if this isn't the right type move on
			if (typeOfThing != 1)
			{
				f.seekg(sizeOfThing);
			}
			
			ui16 nameLength;
			f.read((char*)&nameLength, 2);
			std::string theName;
			for (int j = 0; j < nameLength; j++)
			{
				static char c;
				f.read(&c, 1);
				theName.append(&c);
			}
			
			ui16 pathLength;
			f.read((char*)&pathLength, 2);
			std::string thePath;
			for (int j = 0; j < pathLength; j++)
			{
				static char c;
				f.read(&c, 1);
				thePath.append(&c);
			}
			
			ui8 blendMode;
			f.read((char*)&blendMode, 1);
			
			image* im = createImage(theName);
			im->load(thePath);
			
			imageContainer[entryPosition] = *im;
		}
		
		// read the textures
		for (ui32 i = 0; i < noOfTextures; i++)
		{
			// read type
			ui16 typeOfThing;
			f.read((char*)&typeOfThing, 2);
			
			// position in container
			ui32 entryPosition;
			f.read((char*)&entryPosition, 4);
			
			// size of object
			ui16 sizeOfThing;
			f.read((char*)&sizeOfThing, 2);
			
			// if this isn't the right type move on
			if (typeOfThing != 1)
			{
				f.seekg(sizeOfThing);
			}
			
			ui16 nameLength;
			f.read((char*)&nameLength, 2);
			std::string theName;
			for (int j = 0; j < nameLength; j++)
			{
				static char c;
				f.read(&c, 1);
				theName.append(&c);
			}
			
			// which image to use?
			ui32 imageLink;
			f.read((char*)&imageLink, 4);
			
			// in-image offset
			ui16 xOff = 0, yOff = 0;
			f.read((char*)&xOff, 2);
			f.read((char*)&yOff, 2);
			
			// texture dimentions
			ui16 xSize = 0, ySize = 0;
			f.read((char*)&xSize, 2);
			f.read((char*)&ySize, 2);
			
			// base color
			ui8 col[4] = {0, 0, 0, 0};
			f.read((char*)&col[0], 1);
			f.read((char*)&col[1], 1);
			f.read((char*)&col[2], 1);
			f.read((char*)&col[3], 1);
			
			texture* tx = createTexture(theName);
			tx->setSource(Tree::currentScene->imageRef[imageLink]);
			tx->setOffset(xOff, yOff);
			tx->setSize(xSize, ySize);
			
			tx->r = col[0];
			tx->g = col[1];
			tx->b = col[2];
			tx->a = col[3];
			
			textureContainer[entryPosition] = *tx;
		}
		
		
		// read entities
		for (ui32 i = 0; i < noOfEntities; i++)
		{
			// read type
			ui16 typeOfThing;
			f.read((char*)&typeOfThing, 2);
			
			// position in container
			ui32 entryPosition;
			f.read((char*)&entryPosition, 4);
			
			// size of object
			ui16 sizeOfThing;
			f.read((char*)&sizeOfThing, 2);
			
			// if this isn't the right type move on
			if (typeOfThing != 1)
			{
				f.seekg(sizeOfThing);
			}
			
			ui16 nameLength;
			f.read((char*)&nameLength, 2);
			std::string theName;
			for (int j = 0; j < nameLength; j++)
			{
				static char c;
				f.read(&c, 1);
				theName.append(&c);
			}
			
			// this space reserved for renderObj reading
			int renderLink = 0;
			f.read((char*)&renderLink, 1);
			
			// will this entity draw by default?
			bool willDraw = true;
			f.read((char*)&willDraw, 1);
			
			// Which texture will we use?
			int textureLink = 0;
			f.read((char*)&textureLink, 2);
			
			float position[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
			for (int j = 0; j < 9 ; j++)
			{
				f.read((char*)&position[j], sizeof(float));
				
			}
			
			
			int parentLink = -2;
			f.read((char*)&parentLink, 1);
			
			entity* en = createEntity(theName);
			
			en->draw = willDraw;
			
			en->col = textureRef[textureLink];
			
			en->pos.x = position[0];
			en->pos.y = position[1];
			en->pos.z = position[2];
			en->rot.x = position[3];
			en->rot.y = position[4];
			en->rot.z = position[5];
			en->scl.x = position[6];
			en->scl.y = position[7];
			en->scl.z = position[8];
			
			//nodeContainer
		}
		
		
		// deallocate containers
		memoryManager->deallocate(imageContainer);
		memoryManager->deallocate(textureContainer);
		
		f.close();
		return 0;
	}
	*/
	
	/*
	static int l_dumptofile(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 2)
		{
			scene* sn = Script::checkType<scene>(1);
			//sn->dumpToFile(lua_tostring(L, 2));
		}
		
		return 0;
	}
	
	static int l_loadfromfile(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 2)
		{
			scene* sn = Script::checkType<scene>(1);
			//sn->readFromFile(lua_tostring(L, 2));
		}
		
		return 0;
	}
	*/
	static int l_initAllocators(lua_State* L)
	{
		scene* sn;
		int n = lua_gettop(L);
		if (n == 1)
		{
			sn = Script::checkType<scene>(1);
			sn->assets.init();
			sn->alloced = true;
			
		} else if (n == 2) {
			sn = Script::checkType<scene>(1);
			sn->assets.init((uint)lua_tointeger(L, 2));
			sn->alloced = true;
		}
		return 0;
	}
	
	static const luaL_Reg sceneFuncs[] = {
		//{"dumpToFile", l_dumptofile},
		//{"loadFromFile", l_loadfromfile},
		{"initAllocators", l_initAllocators},
		
		
		{"setParent", l_setParent},
		{"addChild", l_addChild},
		{"removeChild", l_removeChild},
		
		{"setG", l_setG},
		{"setR", l_setR},
		{"setS", l_setS},
		
		{"movG", l_movG},
		{"movR", l_movR},
		{"movS", l_movS},
		
		{"getG", l_getPos},
		{"getR", l_getRot},
		{"getS", l_getScl},
		
		{"setCol", l_setColor},
		{NULL, NULL}
	};
	
	void registerScene(lua_State* L)
	{
		Script::registerType<scene>(sceneFuncs);
	}
	
}