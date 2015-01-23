#include "Tile.h"

Tile::Tile(wxImage* v_Image, unsigned v_PositionX, unsigned v_PositionY, unsigned v_ID, bool v_IsRemoved )
{
    m_Image = v_Image;
    m_PositionX = v_PositionX;
    m_PositionY = v_PositionY;
    m_IsRemoved = v_IsRemoved;
    m_ID = v_ID;
}

Tile::~Tile()
{
    //dtor
}
