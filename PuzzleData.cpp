#include "PuzzleData.h"

PuzzleData::PuzzleData( wxImage* v_Image, wxSize v_DeviceResolution, unsigned int v_CountX, unsigned int v_CountY, unsigned int v_Padding, unsigned int v_Gap )
{
    _image = v_Image;
    _deviceResolution =  v_DeviceResolution;
    _countX = v_CountX;
    _countY = v_CountY;
    _padding = v_Padding;
    _gap = v_Gap;
    _tileImages = new wxImage* [_countY];
    for (unsigned j = 0; j< _countY;++j){
        _tileImages[j] = new wxImage[_countX];
    }
    _tiles = new Tile** [_countY];
    for (unsigned j = 0; j< _countY;++j){
        _tiles[j] = new Tile*[_countX];
    }
}

PuzzleData::~PuzzleData()
{
    /*for (unsigned j = 0; j< m_CountY;++j){
       delete [] m_TileImages[j];
    }
    delete [] m_TileImages;

    for (unsigned j = 0; j< m_CountY;++j){
       delete [] m_Tiles[j];
    }
    delete [] m_Tiles;*/
}


void PuzzleData::cropImage()
{
    unsigned width = _deviceResolution.GetX() - 2*_padding - (_countX-1)*_gap;
    unsigned height = _deviceResolution.GetY() - 2*_padding - (_countY-1)*_gap;
    while ( (width%_countX != 0) && (height%_countY != 0) ) {
        if ( width%_countX != 0 )
            width--;
        if ( height%_countY != 0 )
            height--;
    }
    _tileWidth = width/_countX;
    _tileHeight = height/_countY;
    _image->Rescale(width,height);
    for (unsigned j = 0;j< _countY;++j)
        for (unsigned i=0;i<_countX;++i){
            _tileImages[j][i] = _image->GetSubImage( wxRect( i*_tileWidth, j*_tileHeight, _tileWidth, _tileHeight ) ) ;
        }
    for (unsigned j = 0;j< _countY;++j)
        for (unsigned i=0;i<_countX;++i){
            _tiles[j][i] = new Tile( &_tileImages[j][i],i,j,j*_countX+i );
        }
}

void PuzzleData::draw( wxDC* v_DC )
{
    int gapX, gapY;
    for (unsigned j = 0;j< _countY;++j)
        for (unsigned i=0;i<_countX;++i){
            Tile * pTile = _tiles[j][i];
            if ( !pTile->getIsRemoved() ){
                gapX = i*_gap;
                gapY = j*_gap;
                v_DC->DrawBitmap( *(pTile->getImage()), _padding + i*_tileWidth + gapX,
                                                        _padding + j*_tileHeight + gapY );
            }
        }
}
bool PuzzleData::isCorrectFieldPos(unsigned v_x, unsigned v_y) const{
    if (  v_x < _countX && v_y < _countY  )
        return true;
    else return false;
}

bool PuzzleData::moveTile( unsigned v_x, unsigned v_y )
{
    if ( checkNeighbourSwap(v_x, v_y, v_x+1, v_y) ) {  return true; }
    if ( checkNeighbourSwap(v_x, v_y, v_x, v_y+1) ) {  return true; }
    if ( checkNeighbourSwap(v_x, v_y, v_x-1, v_y) ) {  return true; }
    if ( checkNeighbourSwap(v_x, v_y, v_x, v_y-1) ) {  return true; }
    return false;
}

bool PuzzleData::checkNeighbourSwap( unsigned v_x, unsigned v_y, unsigned v_nx, unsigned v_ny )
{
     if ( isCorrectFieldPos(v_nx,v_ny) && isCorrectFieldPos(v_x,v_y) && _tiles[v_ny][v_nx]->getIsRemoved() ){
        Tile* t = _tiles[v_y][v_x];
        _tiles[v_y][v_x] = _tiles[v_ny][v_nx];
        _tiles[v_ny][v_nx] = t;
        return true;
    }
    else return false;
}

void PuzzleData::moveColumn(unsigned v_column, bool v_topDirection )
{
    if ( isCorrectFieldPos(v_column,0) ){
         if ( v_topDirection ){
            Tile* t = _tiles[0][v_column];
            for (unsigned i=0;i<_countY-1;++i)
                _tiles[i][v_column] = _tiles[i+1][v_column];
            _tiles[_countY-1][v_column] = t;
        } else {
            Tile* t = _tiles[_countY-1][v_column];
            for (unsigned i=_countY-1;i>0;--i)
                _tiles[i][v_column] = _tiles[i-1][v_column];
            _tiles[0][v_column] = t;
        }
    }
}

void PuzzleData::moveRow(unsigned v_row, bool v_rightDirection )
{
    if ( isCorrectFieldPos(0,v_row) ){
         if (! v_rightDirection ){
            Tile* t = _tiles[v_row][0];
            for (unsigned i=0;i<_countX-1;++i)
                _tiles[v_row][i] = _tiles[v_row][i+1];
            _tiles[v_row][_countX-1] = t;
        } else {
            Tile* t = _tiles[v_row][_countX-1];
            for (unsigned i=_countX-1;i>0;--i)
                _tiles[v_row][i] = _tiles[v_row][i-1];
            _tiles[v_row][0] = t;
        }
    }
}

void PuzzleData::removeTile( unsigned v_x, unsigned v_y ){
    if ( isCorrectFieldPos(v_x, v_y) )
        _tiles[v_y][v_x]->setIsRemoved(true);
}

void PuzzleData::mix1()
{
    unsigned x = _countX-1;
    unsigned y = _countY-1;
    removeTile(x,y);
    for (int i=0;i<_countX*_countY*50;++i){
        int r = rand()%4;
        switch ( r ){
        case 0: if(checkNeighbourSwap(x+1,y,x,y)) x=x+1; break;
        case 1: if(checkNeighbourSwap(x,y+1,x,y)) y=y+1; break;
        case 2: if(checkNeighbourSwap(x-1,y,x,y)) x=x-1; break;
        case 3: if(checkNeighbourSwap(x,y-1,x,y)) y=y-1; break;
        }
    }
}

void PuzzleData::mix2()
{
    for (int i=0;i<1000;++i){
        moveColumn( rand()%_countX ,true );
        moveRow( rand()%_countY ,true );
    }
}

bool PuzzleData::isCorrect()
{
    for (int i=0;i<_countX;++i)
        for (int j=0;j<_countY;++j){
            if ( _tiles[i][j]->getID() != i*_countX+j  )
                return false;
        }
    return true;
}
