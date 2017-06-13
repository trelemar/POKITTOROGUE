bool colide(int id, int x, int y, bool c){
    if (entities[id].x == x && entities[id].y == y) return false;
    else return c;
}
bool entitiesLogic(int playerX, int playerY){
    bool nocolide = true;

    for(int i=0; i<entities.size(); ++i){

        switch(entities[i].id){
        case ID_BLOOD:
            if(rand()%10 == 1) entities[i].id = ID_BLOOD_SKELETON;
            break;
        case ID_SCROLL:
            playerHP += rand()%100;
            if(playerHP > 100){playerHP = 100;}
            sprintf(printer,"scroll of healing");
            break;
        case ID_CHEST:
            nocolide = colide(i,playerX,playerY,nocolide); //its wierd but works
            if(!colide(i,playerX,playerY,true)){
                    entities[i].id = ID_CHEST_OPEN;
                    sprintf(printer,"open chest, taken %i gold",  entities[i].hp);
                    playerGold += entities[i].hp;
                    entities[i].hp = 0;
            }
            break;
        case ID_CHEST_OPEN:


            break;
        case ID_BLOOD_SKELETON:
        case ID_RAT:
        case ID_SKELETON_MAGE:
        case ID_SKELETON_ARCHER:
        case ID_SKELETON_WARIOR:
        case ID_MIMIC:
            nocolide = colide(i,playerX,playerY,nocolide); //its wierd but works
            if(entities[i].x > playerX && colide(i,playerX+1,playerY,true)){
                if (!solids[dungeon[entities[i].y][entities[i].x-1]]) entities[i].x-=1;}
            else if(!colide(i,playerX+1,playerY,true)) playerHP -=10;

            if(entities[i].x < playerX && colide(i,playerX-1,playerY,true)){
                if (!solids[dungeon[entities[i].y][entities[i].x+1]]) entities[i].x+=1;}
            else if(!colide(i,playerX-1,playerY,true)) playerHP -=10;

            if(entities[i].y > playerY && colide(i,playerX,playerY+1,true)){
                if (!solids[dungeon[entities[i].y-1][entities[i].x]]) entities[i].y-=1;}
            else if(!colide(i,playerX,playerY+1,true)) playerHP -=10;

            if(entities[i].y < playerY && colide(i,playerX,playerY-1,true)){
                if (!solids[dungeon[entities[i].y+1][entities[i].x]]) entities[i].y+=1;}
            else if(!colide(i,playerX,playerY-1,true)) playerHP -=10;

            if(!colide(i,playerX,playerY,true)){
                entities[i].hp -= 1;

                switch(entities[i].id){
                    case ID_BLOOD_SKELETON:
                        sprintf(printer,"hit blood skeleton, hp: %i",  entities[i].hp);
                        break;
                    case ID_RAT:
                        sprintf(printer,"hit giant rat, hp: %i",  entities[i].hp);
                        break;
                    case ID_SKELETON_MAGE:
                        sprintf(printer,"hit skeleton mage, hp: %i",  entities[i].hp);
                        break;
                    case ID_SKELETON_ARCHER:
                        sprintf(printer,"hit skeleton archer, hp: %i",  entities[i].hp);
                        break;
                    case ID_SKELETON_WARIOR:
                        sprintf(printer,"hit skeleton warior, hp: %i",  entities[i].hp);
                        break;
                    case ID_MIMIC:
                        sprintf(printer,"hit mimic, hp: %i",  entities[i].hp);
                        break;
                }
                if(entities[i].hp <= 0 && entities[i].id == ID_BLOOD_SKELETON){
                    entities[i].id = ID_BLOOD;
                    entities[i].hp = rand()%5;
                }
                else if(entities[i].hp <= 0) removeEntity(i);

            }
            break;
        default:
            printf("unknown entety %i\n", entities[i].id);
            break;
        }
    }
    return nocolide;
}
