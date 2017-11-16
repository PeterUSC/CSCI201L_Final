//
//  LoadLevel.cpp
//  
//
//  Created by Alex Young on 11/12/17.
//
//

#include <stdio.h>

//sstd::string[] levelFiles;
//levelFiles[levelId] = fileName


void Game::LoadLevel(std::string fileName)
{
    std::ifstream file(fileName);
    if(!file.is_open())
    {
        std::cout << ("Failed tp load level: %s", fileName) << std::endl;
    }
    
    size_t row = 0;
    std::string line;
    while(!file.eof())
    {
        std::getLine(file, line);
        for(size_t col = 0; col < line.size(); col++)
        {
            //if not empty space
            if(line[col] != '.')
            {
                //if start position
                if(line[col] == 'S')
                {
                    Vector2 pos;
                    pos.x = 32.0f + 64.0f * col;
                    pos.y = 16.0f + 32.0f * row;
                    player = new Player(this);
                    player->setStart(pos);
                }
                
                //if finish positon
                else if(line[col == 'F')
                {
                    Vector2 pos;
                    pos.x = 32.0f + 64.0f * col;
                    pos.y = 16.0f + 32.0f * row;
                    Finish finish = new Finish(this);
                    finish->setLoc(pos);
                }
                             
                //if enemy positon
                else if(line[col == 'E')
                {
                   Vector2 pos;
                   pos.x = 32.0f + 64.0f * col;
                   pos.y = 16.0f + 32.0f * row;
                   Enemey enemey = new Enemey(this);
                   enemey->setLoc(pos);
                 }
                             
                //if barrier location
                else
                {
                    Vector2 pos;
                    pos.x = 32.0f + 64.0f * col;
                    pos.y = 16.0f + 32.0f * row;
                    Block* b = new Block(this);
                    b->setPosition(pos);
                    b->SetBlockType(line[col]);
                }
            }
        }
        
        row++;
    }
}
