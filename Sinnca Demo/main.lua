print("hello from lua!")

 test = font:new("test")
--test:setSize(16)
--test:setPath(resourcePath .. "Gravity-Light.ttf")
--test:generate()

hi = buffer:new("hi")
--hi:load(resourcePath .. "helloworld.wav")
--[[
source:new("test")
test:setBuffer(hi)

entity:new("player")

image:new("atlas")
atlas:load(resourcePath .. "sinnca sprite.png")

image:new("grass")
grass:load(resourcePath .. "iso_test.png")

texture:new("grassTile")
grassTile:setSource(grass)
grassTile:setOffset(0, 0)

texture:new("sinnca")
sinnca:setSource(atlas)
sinnca:setOffset(0, 0)

player:setCol(sinnca)

grid:new("tiles", 20, 20, true)


for i = 0, 19 do
	for j = 0, 19 do
		tiles:setTex(i, j, grassTile)
	end
end
]]--

for i, k in pairs(_G) do
print(i, k)
end
print("---------------")

for i, k in pairs(___AssetTracker_) do
print(i, k)
end

--test:play()

print("\n\n")

--_root:loadFromFile("firstScene.sinncascene")
--[[
function player:update()
	
	if Key.space:wasPressed() == 1 then
		print("space")
	end
	
end
]]--
--_root:dumpToFile("firstScene")

print("done!")