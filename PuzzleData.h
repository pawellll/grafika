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
        unsigned int getCountX() { return _countX; }
        unsigned int getCountY() { return _countY; }
        Tile *** getTiles() { return _tiles; }
        void draw( wxDC* v_DC );
        void cropImage();
        bool moveTile( unsigned v_x, unsigned v_y );
        void moveColumn(unsigned v_column, bool v_topDirection );
        void moveRow(unsigned v_row, bool v_rightDirection );
        void removeTile( unsigned v_x, unsigned v_y );
        void mix1();
        void mix2();
        bool isCorrect();
    protected:
    private:
        bool isCorrectFieldPos(unsigned v_x, unsigned v_y) const;
        bool checkNeighbourSwap( unsigned v_x, unsigned v_y, unsigned v_nx, unsigned v_ny);

        wxImage* _image;
        wxSize _deviceResolution;
        unsigned int _padding;
        unsigned int _gap;
        unsigned int _countX;
        unsigned int _countY;
        unsigned _tileWidth;
        unsigned _tileHeight;
        Tile *** _tiles;
        wxImage ** _tileImages;
};

#endif // PUZZLEDATA_H
