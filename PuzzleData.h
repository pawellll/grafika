#ifndef PUZZLEDATA_H
#define PUZZLEDATA_H
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/dc.h>
#include "Tile.h"

class PuzzleData
{
    public:
        PuzzleData(){}
        PuzzleData( wxImage* v_Image, wxSize v_DeviceResolution, unsigned int v_CountX, unsigned int v_CountY,
                                                                    unsigned int v_Padding, unsigned int v_Gap );
        virtual ~PuzzleData();
        //PuzzleData(const PuzzleData& other);

        unsigned int GetCountX() { return m_CountX; }
        //void SetCountX(unsigned int val) { m_countX = val; }
        unsigned int GetCountY() { return m_CountY; }
       // void SetCountY(unsigned int val) { m_countY = val; }
        Tile *** GetTiles() { return m_Tiles; }

        void Draw( wxDC* v_DC );
        void CropImage();
        void MoveTile( unsigned v_x, unsigned v_y );
        void MoveColumn(unsigned v_column, bool v_topDirection );
        void MoveRow(unsigned v_row, bool v_rightDirection );
        void RemoveTile( unsigned v_x, unsigned v_y );
        void Mix1();
        void Mix2();
        bool IsCorrect();
        bool ClickAndMove(unsigned v_x, unsigned v_y);
    protected:
    private:
        bool IsCorrectFieldPos(unsigned v_x, unsigned v_y) const;
        bool CheckNeighbourSwap( unsigned v_x, unsigned v_y, unsigned v_nx, unsigned v_ny);

        wxImage* m_Image;
        wxSize m_DeviceResolution;
        unsigned int m_Padding;
        unsigned int m_Gap;
        unsigned int m_CountX;
        unsigned int m_CountY;
        unsigned m_tileWidth;
        unsigned m_tileHeight;
        Tile *** m_Tiles;
        wxImage ** m_TileImages;
};

#endif // PUZZLEDATA_H
