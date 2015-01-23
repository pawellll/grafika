#ifndef TILE_H
#define TILE_H
#include <wx/image.h>

class Tile
{
    public:
        Tile(){}
        Tile( wxImage* v_Image, unsigned v_PositionX, unsigned v_PositionY, unsigned v_ID, bool v_IsRemoved = false );
        virtual ~Tile();

        unsigned int GetPositionX()
        { return m_PositionX; }

        void SetPositionX(unsigned int val)
        { m_PositionX = val; }

        unsigned int GetPositionY()
        { return m_PositionY; }

        void SetPositionY(unsigned int val)
        { m_PositionY = val; }

        bool GetIsRemoved()
        { return m_IsRemoved; }

        void SetIsRemoved(bool val)
        { m_IsRemoved = val; }

        wxImage* GetImage()
        { return m_Image; }

        void SetImage(wxImage* val)
        { m_Image = val; }

        unsigned GetID()
        { return m_ID; }
    protected:
    private:
        unsigned int m_ID;
        unsigned int m_PositionX;
        unsigned int m_PositionY;
        bool m_IsRemoved;
        wxImage* m_Image;
};

#endif // TILE_H
