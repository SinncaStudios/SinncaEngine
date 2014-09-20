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
#include "Utility.h"

namespace sinnca
{
	scene::scene()
	{
		col = &Palette->defaultColor;
		guiManager = Heap->allocateNew<guiMenu>();
		percLoaded = 0.0f;
		perspective = 0; // 2D by defualt
		//entityStorage = memoryManager->heap->allocateNew<PoolAllocator>();
	}
	
	scene::~scene()
	{
		//memoryManager->heap->deallocateDelete(entityStorage);
	}
	
	void scene::onLoad()
	{
		switch (perspective)
		{
			case 0:
				Graphics->ortho(-1.0f, 1.0f);
				break;
				
			case 1:
				Graphics->perspective(100.f, 0.1f, 35.0f);
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
		Graphics->sceneColor(col->toFloat(col->r), col->toFloat(col->g), col->toFloat(col->b));
		
		for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->render();
		}
	}
	
	int scene::pers()
	{
		return perspective;
	}
	/*
	void* scene::operator new(size_t s, std::string n)
	{
		
		Script->newBlankTable();
		
		Script->pushValue(1);
		Script->setMetaTable(-2);
		
		Script->pushValue(1);
		Script->setField(1, "__index");
		
		scene** sn = (scene**)lua_newuserdata(Script->getState(), sizeof(scene*));
		if (Tree->currentScene->sceneStorage != NULL)
		{
			*sn = (scene*)Tree->currentScene->sceneStorage->allocate((unsigned int)s, __alignof(scene));
			
		} else {
			
			*sn = (scene*)Heap->allocate((unsigned int)s, __alignof(scene));
		}
		
		(*sn)->name = n;
		
		Script->getMetaTable("entity");
		Script->setMetaTable(-2);
		
		Script->setField(-2, "__self");
		
		
		Script->setGlobal(n);
		return ((void*)*sn);
	}
	
	void scene::operator delete(void *p)
	{
		if (Tree->currentScene->sceneStorage != NULL)
		{
			Tree->currentScene->sceneStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
		
	}
	*/
	int scene::dumpToFile(std::string file)
	{
		
		std::string wFileExt = file;
		wFileExt.append(".sinncascene");
		//wFileExt.append(".txt");
		// open for writing only
		//f.open(wFileExt);
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
		f.write((const char*)&secondaryHeader, 2);
		
		/*
		// set size of file
		ui64 fSize = sizeof(uint) +
					 sizeof(long) +
					 sizeof(entity) * entityRef.size() +
					 sizeof(grid) * gridRef.size() +
					 sizeof(scene) * sceneRef.size() +
					 sizeof(image) * imageRef.size() +
					 sizeof(texture) * textureRef.size();
		// 8 bytes
		f << fSize;
		 */
		
		// write the number of assets
		// 4 bytes
		ui32 noOfAssets = (ui32)(imageRef.size() +
						  textureRef.size());
		f.write((const char*)&noOfAssets, 4);
		
		// write number of nodes
		// 4 bytes
		ui32 noOfNodes = (ui32)(entityRef.size() +
						 gridRef.size() +
						 sceneRef.size());
		f.write((const char*)&noOfNodes, 4);
		
		
		
		/* ********************************************************************************
		 WRITE IMAGES
		 ******************************************************************************* */
		if (imageRef.size() > 0)
		{
			for (int i = 0; i < imageRef.size(); i++)
			{
				// what kind of asset is this? (2 bytes)
				//f.write((const char*) 1, 2);
				f.put((const char) 1); // 1 = image
				
				// what number asset are we at? (2 bytes)
				f.write((const char*) &i, 2);
				
				// what is the size of this asset? (2 bytes)
				ui16 sizeofthing = sizeof(ui16) + imageRef[i]->name.length() + imageRef[i]->path.length() + ((ui8)imageRef[i]->tb);
				f.write((const char*)&sizeofthing, 2);
				// this is for just in case the engine doesn't support this type of object yet
				
				
				// the size of the name and the name itself
				sizeofthing = imageRef[i]->name.length();
				f.write((const char*)&sizeofthing, 2);
				f << imageRef[i]->name.c_str();
				
				// the size of the filepath and the filepath itself
				sizeofthing = imageRef[i]->path.length();
				f.write((const char*)&sizeofthing, 2);
				f << imageRef[i]->path.c_str();
				
				// the texture blend mode
				f.write((const char*)&imageRef[i]->tb, 1);
				
			}
		}
		
		/* ********************************************************************************
		 WRITE TEXTURES AND COLORS
		 ******************************************************************************* */
		if (textureRef.size() > 0)
		{
			for (int i = 0; i < textureRef.size(); i++)
			{
				// what kind of asset is this? (2 bytes)
				//f.write((const char*) 2, 2);
				f.put((const char) 2); // 2 = texture
				
				// what number asset are we at? (2 bytes)
				f.write((const char*) &i, 2);
				
				// what is the size of this asset? (2 bytes)
				ui16 sizeofthing = (sizeof(ui16) + textureRef[i]->name.length() + (sizeof(ui16) * 5));
				f.write((const char*)&sizeofthing, 2);
				// this is for just in case the engine doesn't support this type of object yet
				
				
				// the size of the name and the name itself
				sizeofthing = textureRef[i]->name.length();
				f.write((const char*)&sizeofthing, 2);
				f << textureRef[i]->name.c_str();
				
				// find the image this texture is linking to
				if (imageRef.size() > 0)
				{
					for (int j = 0; j < imageRef.size(); j++)
					{
						// theres got to be a faster way to do this
						if (imageRef[j] == textureRef[i]->getSource())
						{
							// what image does this texture use? (2 bytes)
							f.write((const char*) &j, 2);
							break;
						}
					}
				}
				
				// write the x and y offset into the file (2 + 2 bytes)
				static int tempx, tempy;
				
				textureRef[i]->getOffset(tempx, tempy);
				f.write((const char*) &tempx, 2);
				f.write((const char*) &tempy, 2);
				
				// write the x and y size into the file (2 + 2 bytes)
				textureRef[i]->getSize(tempx, tempy);
				f.write((const char*) &tempx, 2);
				f.write((const char*) &tempy, 2);
				
				// write the base color
				f.write((const char*)&textureRef[i]->r, 1);
				f.write((const char*)&textureRef[i]->g, 1);
				f.write((const char*)&textureRef[i]->b, 1);
				f.write((const char*)&textureRef[i]->a, 1);
			}
		}
		
		// terminate the asset list, move on to nodes
		//f.write((const char*) -1, 2);
		f.put((const char) -1);
		// -1 is used to tell the engine to move on to other stuff
		
		/* ********************************************************************************
		 WRITE ENTITIES
		 ******************************************************************************* */
		if (entityRef.size() > 0)
		{
			for (int i = 0; i < entityRef.size(); i++)
			{
			
				// put it in!
				//f.write((const char*) 1, 2);
				f.put((const char) 1);
				// 1 = entity
				
				// what number node is this?
				f.write((const char*) &i, 2);
				
				// size of the entity entry
				ui16 sizeofthing = entityRef[i]->name.length() + 26;
				f.write((const char*)&sizeofthing, 2);
				
				
				// name and size of name
				sizeofthing = entityRef[i]->name.length();
				f.write((const char*)&sizeofthing, 2);
				f << entityRef[i]->name.c_str();
				
				// render object
				// currently only supports the sprite class
				//f.write((const char*) 0, 2);
				f.put((const char) 0);
				
				// but is it drawable?
				f.write((const char*) &entityRef[i]->draw, 1);
				
				// color
				for (int j = 0; j < textureRef.size(); j++)
				{
					if (textureRef[j] == entityRef[i]->col)
					{
						f.write((const char*) &j, 2);
						break;
					}
				}
				
				float position[9] = {
					(float)entityRef[i]->pos.x,
					(float)entityRef[i]->pos.y,
					(float)entityRef[i]->pos.z,
					(float)entityRef[i]->rot.x,
					(float)entityRef[i]->rot.y,
					(float)entityRef[i]->rot.z,
					(float)entityRef[i]->scl.x,
					(float)entityRef[i]->scl.y,
					(float)entityRef[i]->scl.z
				};
				
				// entity position
				f.write((const char*) &position[0], sizeof(float));
				f.write((const char*) &position[1], sizeof(float));
				f.write((const char*) &position[2], sizeof(float));
				
				// entity rotation
				f.write((const char*) &position[3], sizeof(float));
				f.write((const char*) &position[4], sizeof(float));
				f.write((const char*) &position[5], sizeof(float));
				
				// entity scale
				f.write((const char*) &position[6], sizeof(float));
				f.write((const char*) &position[7], sizeof(float));
				f.write((const char*) &position[8], sizeof(float));
				
				// find the parent!
				if (entityRef[i]->parent != Tree->currentScene)
				{
					for (int j = 0; j < nodeRef.size(); j++)
					{
						if (entityRef[i]->parent == nodeRef[j])
						{
							f.write((const char*) &j, 2);
						}
					}
					
				} else {
					
					//f.write((const char*) -2, 2);
					f.put((const char) -2);
					// -2 is essentially a null pointer
					// because -1 is "move on" for the loader
				}
				
			}
		}
		
		/* ********************************************************************************
		 WRITE GRIDS
		 ******************************************************************************* */
		if (gridRef.size() > 0)
		{
			for (int i = 0; i < gridRef.size(); i++)
			{
				// put it in!
				//f.write((const char*) 2, 2);
				f.put((const char) 2);
				// 2 = grid
				
				// what number node is this?
				f.write((const char*) &i, 2);
				
				// size of the grid entry
				ui16 sizeofthing = gridRef[i]->name.length() + 30 + ((gridRef[i]->getX() * gridRef[i]->getY()) * 2);
				f.write((const char*)&sizeofthing, 2);
				
				// name and size of name
				sizeofthing = gridRef[i]->name.length();
				f.write((const char*)&sizeofthing, 2);
				f << gridRef[i]->name.c_str();
				
				// render object
				// currently only supports the sprite class
				//f.write((const char*) 0, 2);
				f.put((const char) 0);
				
				// but is it drawable?
				f.write((const char*) &gridRef[i]->draw, 1);
				
				// isometric or not?
				f.write((const char*) &gridRef[i]->iso, 1);
				
				// color
				// we don't need it for the whole grid
				
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
				
				// find the parent!
				if (gridRef[i]->parent != nullptr)
				{
					for (int j = 0; j < nodeRef.size(); j++)
					{
						if (gridRef[i]->parent == nodeRef[j])
						{
							f.write((const char*) &j, 2);
						}
					}
					
				} else {
					
					//f.write((const char*) -2, 2);
					f.put((const char) -2);
					// -2 is essentially a null pointer
					// because -1 is "move on" for the loader
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
		/*
		std::streampos pos = f.tellg();
		char* buffer = (char*)Heap->allocate(pos, __alignof(char*));
		
		// read the file
		f.seekg(0, std::ios::beg);
		f.read(buffer, pos);
		f.close();
		// now we're done with the file and we can read from the buffer
		*/
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
		
		ui32 noOfAssets = 0;
		f.read((char*)&noOfAssets, 4);
		ui32 noOfNodes = 0;
		f.read((char*)&noOfNodes, 4);
		
		for (int i = 0; i < noOfAssets; i++)
		{
			int obType = 0, numAsset = 0, assetSize = 0;
			
			f.read((char*)&obType, 1);
			f.read((char*)&numAsset, 2);
			f.read((char*)&assetSize, 2);
			
			switch (obType)
			{
				case 1:
				{
					// It's an image!
					int nameSize = 0;
					f.read((char*)&nameSize, 2);
					
					std::string thingName;
					for (int j = 0; j < nameSize; j++)
					{
						static char c;
						f.read(&c, 1);
						thingName.append(&c);
					}
					
					
					// how long is the path?
					int pathSize = 0;
					f.read((char*)&pathSize, 2);
					// and the path itself
					std::string pathName;
					for (int j = 0; j < pathSize; j++)
					{
						static char c;
						f.read(&c, 1);
						pathName.append(&c);
					}
					
					
					ui8 blendMode = 0;
					f.read((char*)&blendMode, 1);
					
					
					image* im = createImage(thingName);
					im->load(pathName, (texBlend)blendMode);
					Tree->currentScene->imageRef.push_back(im);
					
					break;
				}
				case 2:
				{
					// It's a texture!
					// how long is the name?
					int nameSize = 0;
					f.read((char*)&nameSize, 2);
					// and the name itself
					std::string thingName;
					for (int j = 0; j < nameSize; j++)
					{
						static char c;
						f.read(&c, 1);
						thingName.append(&c);
					}
					
					int imageLink = 0;
					f.read((char*)&imageLink, 2);
					
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
					
					texture* tx = createTexture(thingName);
					tx->setSource(Tree->currentScene->imageRef[imageLink]);
					tx->setOffset(xOff, yOff);
					//tx->setSize(xSize, ySize);
					
					tx->r = col[0];
					tx->g = col[1];
					tx->b = col[2];
					tx->a = col[3];
					Tree->currentScene->textureRef.push_back(tx);
					
					break;
				}
				default:
				{
					int nameSize = 0;
					f.read((char*)&nameSize, 2);
					
					std::string thingName;
					f.read((char*)&thingName, nameSize);
					printf("Object '%s' was not recognized by this version of the engine. A newer version may be required or there was a mis-write when the file was created", thingName.c_str());
					
					break;
				}
			}
		}
		
		int tempint = 0;
		f.read((char*)&tempint, 1);
		
		for (int i = 0; i < noOfNodes; i++)
		{
			int obType = 0, numNode = 0, nodeSize = 0;
			
			f.read((char*)&obType, 1);
			f.read((char*)&numNode, 2);
			f.read((char*)&nodeSize, 2);
			
			switch (obType)
			{
				case 1:
				{
					// It's an entity!
					int nameSize = 0;
					f.read((char*)&nameSize, 2);
					
					std::string thingName;
					for (int j = 0; j < nameSize; j++)
					{
						static char c;
						f.read(&c, 1);
						thingName.append(&c);
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
					
					entity* en = createEntity(thingName);
					
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
					
					if (parentLink == -2 || parentLink < 0)
					{
						en->parent = this;
						
					} else {
						
						en->parent = nodeRef[parentLink];
					}
					Tree->currentScene->nodeRef.push_back(en);
					
					break;
				}
				
				case 2:
				{
					// It's a grid!
					int nameSize = 0;
					f.read((char*)&nameSize, 2);
					
					std::string thingName;
					for (int j = 0; j < nameSize; j++)
					{
						static char c;
						f.read(&c, 1);
						thingName.append(&c);
					}
					
					// this space reserved for renderObj reading
					int renderLink = 0;
					f.read((char*)&renderLink, 1);
					
					// will this grid draw by default?
					bool willDraw = true;
					f.read((char*)&willDraw, 1);
					
					// is it isometric?
					bool isIso = true;
					f.read((char*)&isIso, 1);
					
					// How big is it?
					uint sizeX, sizeY;
					f.read((char*)&sizeX, 2);
					f.read((char*)&sizeY, 2);
					
					// create the grid now
					grid* gd = createGrid(thingName, sizeX, sizeY, isIso);
					
					for(int j = 0; j < sizeX; j++)
					{
						for(int k = 0; k < sizeY; k++)
						{
							static bool tempSolid;
							f.read((char*)&tempSolid, 1);
							
							gd->setSolid(j, k, tempSolid);
							
							static int textureLink;
							f.read((char*)&textureLink, 2);
							gd->setTexture(j, k, textureRef[textureLink]);
						}
					}
					
					float position[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
					for (int j = 0; j < 9 ; j++)
					{
						f.read((char*)&position[j], sizeof(float));
						
					}
					
					int parentLink = -2;
					f.read((char*)&parentLink, 1);
					
					gd->draw = willDraw;
					
					
					gd->pos.x = position[0];
					gd->pos.y = position[1];
					gd->pos.z = position[2];
					gd->rot.x = position[3];
					gd->rot.y = position[4];
					gd->rot.z = position[5];
					gd->scl.x = position[6];
					gd->scl.y = position[7];
					gd->scl.z = position[8];
					
					if (parentLink == -2 || parentLink < 0)
					{
						gd->parent = this;
						
					} else {
						
						gd->parent = nodeRef[parentLink];
					}
					Tree->currentScene->nodeRef.push_back(gd);
					
					break;
				}
				default:
				{
					int nameSize = 0;
					f.read((char*)&nameSize, 2);
					
					std::string thingName;
					f.read((char*)&thingName, nameSize);
					printf("Object '%s' was not recognized by this version of the engine. A newer version may be required or there was a mis-write when the file was created", thingName.c_str());
					
					
					break;
				}
			}
		}
		
		f.close();
		return 0;
	}
	
	scene* checkScene(int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(Script->getState(), ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(Script->getState(), "__self");
		// get our table
		lua_gettable(Script->getState(), ind);
		
		// cast userdata pointer to "Node" type
		ud = dynamic_cast<scene*>((scene*)lua_touserdata(Script->getState(), -1));
		luaL_argcheck(Script->getState(), ud != 0, ind, "Incompatible 'entity' type...");
		
		return *((scene**)ud);
		
	}
	
	static int l_dumptofile(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 2)
		{
			scene* sn = checkScene(1);
			sn->dumpToFile(lua_tostring(L, 2));
		}
		
		return 0;
	}
	
	static int l_loadfromfile(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 2)
		{
			scene* sn = checkScene(1);
			sn->readFromFile(lua_tostring(L, 2));
		}
		
		return 0;
	}
	
	static const luaL_Reg sceneFuncs[] = {
		{"dumpToFile", l_dumptofile},
		{"loadFromFile", l_loadfromfile},
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
		
		luaL_newmetatable(L, "scene");
		
		
		luaL_register(L, 0, sceneFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		
		
		luaL_register(L, "scene", sceneFuncs);
			
	}
	
}