function idle(me)
   delay(2000)
   print("NPC 2: I'm moving NPC 1 now") 
   move('npc1', tilesToPixels(0), tilesToPixels(4))
   move("npc1", tilesToPixels(4), tilesToPixels(4))
   move("npc1", tilesToPixels(4), tilesToPixels(0))
   move("npc1", tilesToPixels(0), tilesToPixels(0))
end