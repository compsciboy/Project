My implementation created a pile of 9 rooms using struct room, 4 item rooms, 2 omen rooms, and 2 event rooms and each item room contain a struct item, while the rest room have a linkedlist of null items. There is no no other rooms in the game board except the starting room, and there is no item, omen and event in the starting room. 

There is an avatar that has an inventory that the player can control, the player can control the avatar to go to different rooms, take items, drop items, see the room, and look at inventory using input command.

The go Direction command allow the avatar to move through each room in direction north, east, west, up, and down, I implemented my game so that the avator can't go south. The take ITEM command allow the avatar to take item from the room and add it to its inventory. The drop ITEM command allow the avatar to drop item from the inventory to the room. The look command prints out the items in the room and the rooms in each direction, and the inventory command allow the player to see the items in inventory.

There is a winning and losing state where the player win if the avatar is in the starting room with atleast 2 items and 1 omen, and the player lose is wants to explore a new room but the room pile is empty.

