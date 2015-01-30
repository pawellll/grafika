#include "Tile.h"

Tile::Tile(wxImage* v_Image, unsigned v_PositionX, unsigned v_PositionY, unsigned v_ID, bool v_IsRemoved )
{
    _image = v_Image;
    _positionX = v_PositionX;
    _positionY = v_PositionY;
    _isRemoved = v_IsRemoved;
    _ID = v_ID;
}

Tile::~Tile()
{
    //dtor
}
