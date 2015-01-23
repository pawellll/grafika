#include "PuzzleData.h"

PuzzleData::PuzzleData( wxImage* v_Image, wxSize v_DeviceResolution, unsigned int v_CountX, unsigned int v_CountY, unsigned int v_Padding, unsigned int v_Gap )
{
    m_Image = v_Image;
    m_DeviceResolution =  v_DeviceResolution;
    m_CountX = v_CountX;
    m_CountY = v_CountY;
    m_Padding = v_Padding;
    m_Gap = v_Gap;
    m_TileImages = new wxImage* [m_CountY];
    for (unsigned j = 0; j< m_CountY;++j){
        m_TileImages[j] = new wxImage[m_CountX];
    }
    m_Tiles = new Tile** [m_CountY];
    for (unsigned j = 0; j< m_CountY;++j){
        m_Tiles[j] = new Tile*[m_CountX];
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


void PuzzleData::CropImage()
{
    unsigned width = m_DeviceResolution.GetX() - 2*m_Padding - (m_CountX-1)*m_Gap;
    unsigned height = m_DeviceResolution.GetY() - 2*m_Padding - (m_CountY-1)*m_Gap;
    while ( (width%m_CountX != 0) && (height%m_CountY != 0) ) {
        if ( width%m_CountX != 0 )
            width--;
        if ( height%m_CountY != 0 )
            height--;
    }
    m_tileWidth = width/m_CountX;
    m_tileHeight = height/m_CountY;
    m_Image->Rescale(width,height);
    for (unsigned j = 0;j< m_CountY;++j)
        for (unsigned i=0;i<m_CountX;++i){
            m_TileImages[j][i] = m_Image->GetSubImage( wxRect( i*m_tileWidth, j*m_tileHeight, m_tileWidth, m_tileHeight ) ) ;
        }
    for (unsigned j = 0;j< m_CountY;++j)
        for (unsigned i=0;i<m_CountX;++i){
            m_Tiles[j][i] = new Tile( &m_TileImages[j][i],i,j,j*m_CountX+i );
        }
}

void PuzzleData::Draw( wxDC* v_DC )
{
    int gapX, gapY;
    for (unsigned j = 0;j< m_CountY;++j)
        for (unsigned i=0;i<m_CountX;++i){
            Tile * pTile = m_Tiles[j][i];
            if ( !pTile->GetIsRemoved() ){
                gapX = i*m_Gap;
                gapY = j*m_Gap;
                v_DC->DrawBitmap( *(pTile->GetImage()), m_Padding + i*m_tileWidth + gapX,
                                                        m_Padding + j*m_tileHeight + gapY );
            }
        }
}
bool PuzzleData::IsCorrectFieldPos(unsigned v_x, unsigned v_y) const{
    if (  v_x < m_CountX && v_y < m_CountY  )
        return true;
    else return false;
}

void PuzzleData::MoveTile( unsigned v_x, unsigned v_y )
{
    if ( CheckNeighbourSwap(v_x, v_y, v_x+1, v_y) ) {  return; }
    if ( CheckNeighbourSwap(v_x, v_y, v_x, v_y+1) ) {  return; }
    if ( CheckNeighbourSwap(v_x, v_y, v_x-1, v_y) ) {  return; }
    if ( CheckNeighbourSwap(v_x, v_y, v_x, v_y-1) ) {  return; }
}

bool PuzzleData::CheckNeighbourSwap( unsigned v_x, unsigned v_y, unsigned v_nx, unsigned v_ny )
{
     if ( IsCorrectFieldPos(v_nx,v_ny) && IsCorrectFieldPos(v_x,v_y) && m_Tiles[v_ny][v_nx]->GetIsRemoved() ){
        Tile* t = m_Tiles[v_y][v_x];
        m_Tiles[v_y][v_x] = m_Tiles[v_ny][v_nx];
        m_Tiles[v_ny][v_nx] = t;
        return true;
    }
    else return false;
}

void PuzzleData::MoveColumn(unsigned v_column, bool v_topDirection )
{
    if ( IsCorrectFieldPos(v_column,0) ){
         if ( v_topDirection ){
            Tile* t = m_Tiles[0][v_column];
            for (unsigned i=0;i<m_CountY-1;++i)
                m_Tiles[i][v_column] = m_Tiles[i+1][v_column];
            m_Tiles[m_CountY-1][v_column] = t;
        } else {
            Tile* t = m_Tiles[m_CountY-1][v_column];
            for (unsigned i=m_CountY-1;i>0;--i)
                m_Tiles[i][v_column] = m_Tiles[i-1][v_column];
            m_Tiles[0][v_column] = t;
        }
    }
}

void PuzzleData::MoveRow(unsigned v_row, bool v_rightDirection )
{
    if ( IsCorrectFieldPos(0,v_row) ){
         if (! v_rightDirection ){
            Tile* t = m_Tiles[v_row][0];
            for (unsigned i=0;i<m_CountX-1;++i)
                m_Tiles[v_row][i] = m_Tiles[v_row][i+1];
            m_Tiles[v_row][m_CountX-1] = t;
        } else {
            Tile* t = m_Tiles[v_row][m_CountX-1];
            for (unsigned i=m_CountX-1;i>0;--i)
                m_Tiles[v_row][i] = m_Tiles[v_row][i-1];
            m_Tiles[v_row][0] = t;
        }
    }
}

void PuzzleData::RemoveTile( unsigned v_x, unsigned v_y ){
    if ( IsCorrectFieldPos(v_x, v_y) )
        m_Tiles[v_y][v_x]->SetIsRemoved(true);
}

void PuzzleData::Mix1()
{
    unsigned x = m_CountX-1;
    unsigned y = m_CountY-1;
    RemoveTile(x,y);
    for (int i=0;i<m_CountX*m_CountY*50;++i){
        int r = rand()%4;
        switch ( r ){
        case 0: if(CheckNeighbourSwap(x+1,y,x,y)) x=x+1; break;
        case 1: if(CheckNeighbourSwap(x,y+1,x,y)) y=y+1; break;
        case 2: if(CheckNeighbourSwap(x-1,y,x,y)) x=x-1; break;
        case 3: if(CheckNeighbourSwap(x,y-1,x,y)) y=y-1; break;
        }
    }
}

void PuzzleData::Mix2()
{
    for (int i=0;i<1000;++i){
        MoveColumn( rand()%m_CountX ,true );
        MoveRow( rand()%m_CountY ,true );
    }
}

bool PuzzleData::IsCorrect()
{
    for (int i=0;i<m_CountX;++i)
        for (int j=0;j<m_CountY;++j){
            if ( m_Tiles[i][j]->GetID() != i*m_CountX+j  )
                return false;
        }
    return true;
}

bool PuzzleData::ClickAndMove(unsigned v_x, unsigned v_y)
{
    int x = v_x - m_Padding;
    int xd = x%(m_tileWidth+m_Gap);
    if ( x > m_tileWidth )
        return false;
    int tile_x = x/(m_tileWidth+m_Gap);
    if ( tile_x >= m_CountX )
        return false;
    int y = v_y - m_Padding;
    int yd = y%(m_tileHeight+m_Gap);
    if ( y > m_tileHeight )
        return false;
    int tile_y = y/(m_tileHeight+m_Gap);
    if ( tile_y >= m_CountY )
        return false;
    if ( !m_Tiles[tile_y][tile_x]->GetIsRemoved() ){
        MoveTile(tile_x,tile_y);
        return true;
    }
    return false;
}
