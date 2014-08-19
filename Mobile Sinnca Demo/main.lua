print("hello from lua!")

entity:new("player")

for i, k in pairs(_G) do
print(i, k)
end

print("\n\n")

for i, k in pairs(player) do
print(i, k)
end

function player:update()



end
