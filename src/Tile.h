#ifndef TILE_H
#define TILE_H
#include <wx/image.h>

class Tile
{
    public:
        Tile(){}
        Tile( wxImage* v_Image, unsigned v_PositionX, unsigned v_PositionY, unsigned v_ID, bool v_IsRemoved = false );
        virtual ~Tile();

        unsigned int getPositionX()
        { return _positionX; }

        void setPositionX(unsigned int val)
        { _positionX = val; }

        unsigned int getPositionY()
        { return _positionY; }

        void setPositionY(unsigned int val)
        { _positionY = val; }

        bool getIsRemoved()
        { return _isRemoved; }

        void setIsRemoved(bool val)
        { _isRemoved = val; }

        wxImage* getImage()
        { return _image; }

        void setImage(wxImage* val)
        { _image = val; }

        unsigned getID()
        { return _ID; }
    protected:
    private:
        unsigned int _ID;
        unsigned int _positionX;
        unsigned int _positionY;
        bool _isRemoved;
        wxImage* _image;
};

#endif // TILE_H
