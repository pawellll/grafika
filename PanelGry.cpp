#include "PanelGry.h"
#include "ProjektMain.h"

BEGIN_EVENT_TABLE(PanelGry,wxPanel)
    EVT_UPDATE_UI(ID_PANEL1, PanelGry::updateUI)
    EVT_BUTTON(ID_BACK,PanelGry::backClick)
    EVT_BUTTON(ID_PAUSE,PanelGry::pauseClick)
    EVT_KEY_UP(PanelGry::keyUp)
    EVT_CHAR_HOOK(PanelGry::keyDown)
    //EVT_PAINT(PanelGry::PaintEvt)
    //EVT_TIMER(ID_TIMER, PanelGry::OnTimer)
END_EVENT_TABLE()

PanelGry::PanelGry(wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name, wxImage img, int gameSize, bool gameType) 
:   wxPanel(parent,ID,pos,size,style|wxWANTS_CHARS,name){
       
    _panel1 = new wxPanel(this, ID_PANEL1, wxPoint(25,0), wxSize(500,500), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    _panel1->SetMinSize(wxSize(500,500));
    _panel1->SetMaxSize(wxSize(500,500));
    _panel1 -> SetBackgroundColour("GREEN");
    _buttonBack = new wxButton(this,ID_BACK,wxString("Wróæ"),wxPoint(600,20), wxSize(80,35),0,wxDefaultValidator, "BACK_GAME");
    _buttonPause = new wxButton(this,ID_PAUSE,wxString("Pauza"),wxPoint(700,20), wxSize(80,35),0,wxDefaultValidator, "PAUSE_GAME"); 
           
    _pause = false;
    image = img;
    //wxImageHandler * jpgLoader = new wxJPEGHandler();
    //wxImage::AddHandler(jpgLoader);

    //image.LoadFile("obraz.jpg",wxBITMAP_TYPE_JPEG );
    ///if (image.IsOk())
    ///    SetTitle("ok");
    wxSize panelSize = _panel1->GetSize();
    data = PuzzleData(&image,panelSize,gameSize,gameSize,30,5);
    data.CropImage();
    //data.Mix1();
    //data.RemoveTile(9,9);
   // data.MoveTile(9,8);
   // data.MoveColumn(0,false);
    //data.MoveRow(0,true);
    _imagePreview = new wxBitmapButton(this,ID_ICON, wxBitmap( image.Scale(500,500) ), wxPoint(25,0), wxSize(500,500), 0, wxDefaultValidator, "PREVIEW"); 
    _imagePreview -> Hide();   
    

}

PanelGry::~PanelGry(){
    //(*Destroy(ProjektFrame)
    //*)
}

void PanelGry::updateUI(wxUpdateUIEvent & event){
    paint();
}

void PanelGry::paint(){
    wxClientDC dcClient( _panel1 );
    wxBufferedDC dc(&dcClient);
    dc.Clear();
    data.Draw( &dc );
}

void PanelGry::backClick(wxCommandEvent& event){
    _pause = false;
    pauseClick(event);
    ProjektFrame::FRAME->setState(STATE_OPTIONS);   
}


void PanelGry::pauseClick(wxCommandEvent& event){
    if(_pause)
        _buttonPause->SetLabel("Pauza");
    else
        _buttonPause->SetLabel("Kontynuuj");    
    _pause = !_pause;      
}

void PanelGry::keyDown(wxKeyEvent& event){
    if(event.GetKeyCode() == 9){
        _panel1 -> Hide();
        _imagePreview -> Show();
    }  
}
    
void PanelGry::keyUp(wxKeyEvent& event){
    if(event.GetKeyCode() == 9){
        _panel1 -> Show();
        _imagePreview -> Hide();
    }  
}

bool PanelGry::paused(){
    return _pause;   
}

void PanelGry::paintEvt(wxPaintEvent& event){
    /*wxPaintDC dc(this);
    std::cout<<"print\n";
    //dc.Clear();
    //data.Draw(&dc);
    dc.DrawRotatedText("MY ROTATED TEXT...",200,200,3);
    if ( data.GetIsAnimated())
    {

        data.ProccessAnim(1);
        data.DrawTileAnim(&dc);
    } else {
        data.Draw(&dc);
    }*/
}

/*void PanelGry::OnTimer(wxTimerEvent& event){

}*/
