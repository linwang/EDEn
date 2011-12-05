function idle(me)
   delay(5000)
   print("NPC 2: I'm laughing!")
   setAnimation('npc2', 'laughing')
   print("NPC 2: I'm moving after a 5 second wait!")
   move('npc2', tilesToPixels(random(1,20)), tilesToPixels(random(1,20)))
   delay(5000)
   print("NPC 2: I'm moving NPC 1 after a 5 second wait!")
   move('npc1', tilesToPixels(0), tilesToPixels(4))
   print("NPC 2: Not funny anymore.")
   setSprite('npc2', 'stand_down')
end
