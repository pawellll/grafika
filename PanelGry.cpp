#include "PanelGry.h"
#include "ProjektMain.h"
#include <iostream>
#include <sstream>
#include "math.h"

BEGIN_EVENT_TABLE(GameSubPanel,wxPanel)
    EVT_LEFT_DOWN(GameSubPanel::mouseDown)
    EVT_LEFT_UP(GameSubPanel::mouseUp)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(PanelGry,wxPanel)
    EVT_UPDATE_UI(ID_PANEL1, PanelGry::updateUI)
    EVT_BUTTON(ID_BACK,PanelGry::backClick)
    EVT_BUTTON(ID_PAUSE,PanelGry::pauseClick)
    EVT_KEY_UP(PanelGry::keyUp)
    EVT_KEY_DOWN(PanelGry::keyDown)
    EVT_CHAR_HOOK(PanelGry::keyDown)
    EVT_CHAR(PanelGry::keyDown)
    EVT_LEFT_UP(PanelGry::mouseUp)
    EVT_TIMER(ID_TIMER, PanelGry::OnTimer)
END_EVENT_TABLE()

/*
    GameSubPanel
*/

GameStats GameSubPanel::LAST_STATS(0,false);

GameSubPanel::GameSubPanel(wxWindow * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name, wxImage & img, int gameSize, bool gameType)
:   wxPanel(parent,ID,pos,size,style|wxWANTS_CHARS,name){
    image = img;
    _tiles = gameSize;
    _type = gameType;
    wxSize panelSize = this->GetSize();
    
    data = PuzzleData(&image,panelSize,gameSize,gameSize,10,5);
    data.CropImage();
    if(_type)
        data.Mix1();
    else
        data.Mix2();
    _moves = 0;
}

GameSubPanel::~GameSubPanel(){    
}

void GameSubPanel::mouseDown(wxMouseEvent& event){
    wxPoint pos = wxGetMousePosition() - GetScreenPosition();  
    if(!_type) {
        _lastX = pos.x;
        _lastY = pos.y;   
        return;
    }  
    if (data.MoveTile(  pos.x / (GetSize().GetWidth() /_tiles),
                        pos.y / (GetSize().GetHeight()/_tiles) ) 
        ) _moves ++;               
    
    if(data.IsCorrect()) gameFinished();
}

void GameSubPanel::mouseUp(wxMouseEvent& event){
    if(_type) return;
    wxPoint pos = wxGetMousePosition() - GetScreenPosition();  
    int dx = pos.x - _lastX;
    int dy = pos.y - _lastY;
    if(dx < 10 && dy < 10 && abs(dx - dy) < 10) return;
    _moves ++; 
    if(abs(dx) > abs(dy))
        data.MoveRow(_lastY / (GetSize().GetHeight()/_tiles ),dx > 0) ;        
    else
        data.MoveColumn(_lastX / (GetSize().GetWidth()/_tiles),dy < 0);
        
    if(data.IsCorrect()) gameFinished();    
}

void GameSubPanel::paint(){
    wxClientDC dcClient( this );
    wxBufferedDC dc(&dcClient);
    dc.Clear();
    data.Draw( &dc );
}

void GameSubPanel::updateUI(wxUpdateUIEvent & event){
    paint();
}

void GameSubPanel::gameFinished(){
        LAST_STATS.gameType = _type;
        LAST_STATS.level = _tiles;
        LAST_STATS.moves = _moves;
        paint();
        wxMessageDialog a (this,"Wygra³eœ!",wxMessageBoxCaptionStr, wxOK);
        a.ShowModal();        
        ProjektFrame::FRAME -> gameFinished();
        
}

/*********************************************************************************

    GamePanel
    
**********************************************************************************/ 

PanelGry::PanelGry(wxWindow * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name, wxImage img, int gameSize, bool gameType) 
:   wxPanel(parent,ID,pos,size,style|wxWANTS_CHARS,name){
       
    _panel1 = new GameSubPanel(this, ID_PANEL1, wxPoint(25,0), wxSize(500,500), wxTAB_TRAVERSAL, _T("ID_PANEL1"),img,gameSize, gameType);
    _panel1->SetMinSize(wxSize(500,500));
    _panel1->SetMaxSize(wxSize(500,500));
    _buttonBack = new wxButton(this,ID_BACK,wxString("Wróæ"),wxPoint(600,20), wxSize(80,35),0,wxDefaultValidator, "BACK_GAME");
    _buttonPause = new wxButton(this,ID_PAUSE,wxString("Pauza"),wxPoint(700,20), wxSize(80,35),0,wxDefaultValidator, "PAUSE_GAME"); 
           
    _pause = false;
    image = img;
    _time = 0;
    _moves = 0;
    
    _imagePreview = new wxBitmapButton(this,ID_ICON, wxBitmap( image.Rescale(500,500) ), wxPoint(25,0), wxSize(500,500), 0, wxDefaultValidator, "PREVIEW"); 
    _imagePreview -> Hide();  
    //_imagePreview -> Enable(false);
    
    SetFocusIgnoringChildren ();
    _textTime = new wxStaticText(this, ID_TEXT1, wxT("Czas : 0s"), wxPoint(600,70), wxDefaultSize, 0, wxT("WxStaticText2"));
    _textMoves = new wxStaticText(this, ID_TEXT2, wxT("Ruchy : 0"), wxPoint(600,100), wxDefaultSize, 0, wxT("WxStaticText2"));
    static const int INTERVAL = 1000; // milliseconds
    _timer = new wxTimer(this, ID_TIMER);
    _timer->Start(INTERVAL);
}

PanelGry::~PanelGry(){
    _timer -> Stop();
    delete _timer;
}

void PanelGry::updateUI(wxUpdateUIEvent & event){
    paint();
}

void PanelGry::backClick(wxCommandEvent& event){
    _pause = false;
    pauseClick(event);
    ProjektFrame::FRAME->setState(STATE_OPTIONS);   
}

void PanelGry::pauseClick(wxCommandEvent& event){
    SetFocusIgnoringChildren ();
    if(_pause){
        _buttonPause->SetLabel("Pauza");
        _imagePreview -> Enable(true);
        _panel1 -> Show();
        _imagePreview -> Hide();
        }
    else{
        _buttonPause->SetLabel("Kontynuuj");  
        _imagePreview -> Enable(false);
        _panel1 -> Hide();
        _imagePreview -> Show();
        }  
    SetFocusIgnoringChildren ();
    _pause = !_pause;      
}

bool PanelGry::paused(){
    return _pause;   
}

void PanelGry::paint(){
    _panel1->paint();  
    
    if(_moves != _panel1->_moves){
        _moves = _panel1->_moves;
        std::ostringstream sstream;
        sstream << "Ruchy : " << _moves ;
        _textMoves->SetLabel(sstream.str());
    }
}

void PanelGry::keyDown(wxKeyEvent& event){
    if(event.GetKeyCode() == 9){
        if(_pause)return;
        _panel1 -> Hide();     
        _imagePreview -> Show();   
        _imagePreview -> Enable(true);
    }  
}
    
void PanelGry::keyUp(wxKeyEvent& event){
    if(event.GetKeyCode() == 9){
        if(_pause)return;
        _imagePreview -> Enable(false);
        _imagePreview -> Hide();
        _panel1 -> Show();
    }  
}

void PanelGry::OnTimer(wxTimerEvent& event){
    if(!_pause) {
        SetFocusIgnoringChildren ();
        _time ++;    
        std::ostringstream sstream;
        sstream << "Czas : "<< _time << "s";
        _textTime->SetLabel(sstream.str());
    }
}
