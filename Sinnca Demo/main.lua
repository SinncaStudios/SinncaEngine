print("hello from lua!")


testscene = scene:new()

test = font:new()
test:setSize(16)
test:setPath(resourcePath .. "Gravity-Light.ttf")
test:generate()

hi = buffer:new()
hi:load(resourcePath .. "helloworld.wav")

test = source:new()
test:setBuffer(hi)

player = entity:new()

atlas = image:new()
atlas:load(resourcePath .. "sinnca sprite.png")

grass = image:new()
grass:load(resourcePath .. "iso_test.png")

grassTile = texture:new()
grassTile:setSource(grass)
grassTile:setOffset(0, 0)

sinnca = texture:new()
sinnca:setSource(atlas)
sinnca:setOffset(0, 0)

player:setCol(sinnca)

tiles = grid:new(20, 20, true)

for i = 0, 19 do
	for j = 0, 19 do
		tiles:setTex(i, j, grassTile)
	end
end


for i, k in pairs(_G) do
print(i, k)
end
print("---")
for i, k in pairs(root) do
print(i, k)
end
print("---")
for i, k in pairs(sinnca) do
print(i, k)
end
root:initAllocators()
--testscene:initAllocators()

test:play()

print("\n\n")

--_root:loadFromFile("firstScene.sinncascene")

function player:update()
	
	if Key.space:wasPressed() == 1 then
		print("space")
	end
	
end

--_root:dumpToFile("firstScene")

print("done!")