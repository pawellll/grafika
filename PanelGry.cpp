#include "PanelGry.h"
#include "ProjektMain.h"

#include <wx/msgdlg.h>

#include <wx/intl.h>
#include <wx/string.h>


BEGIN_EVENT_TABLE(PanelGry,wxPanel)
    EVT_UPDATE_UI(ID_PANEL1, PanelGry::UpdateUI)
    EVT_BUTTON(ID_BACK,PanelGry::BackClick)
    EVT_BUTTON(ID_PAUSE,PanelGry::PauseClick)
    //EVT_PAINT(PanelGry::PaintEvt)
    //EVT_TIMER(ID_TIMER, PanelGry::OnTimer)
END_EVENT_TABLE()

PanelGry::PanelGry(wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name) 
:   wxPanel(parent,ID,pos,size,style,name){
       
    //Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(600,600), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    //Panel1->SetMinSize(wxSize(600,600));
    //Panel1->SetMaxSize(wxSize(600,600));
        
    _buttonBack = new wxButton(this,ID_BACK,wxString("Wróæ"),wxPoint(600,20), wxSize(80,35),0,wxDefaultValidator, "BACK_GAME");
    _buttonPause = new wxButton(this,ID_PAUSE,wxString("Pauza"),wxPoint(700,20), wxSize(80,35),0,wxDefaultValidator, "PAUSE_GAME"); 
     
       
    _pause = false;
    /*
    wxImageHandler * pngLoader = new wxJPEGHandler();
    wxImage::AddHandler(pngLoader);

    image.LoadFile("obraz.jpg",wxBITMAP_TYPE_JPEG );
    ///if (image.IsOk())
    ///    SetTitle("ok");
    wxSize panelSize = Panel1->GetSize();
    data = PuzzleData(&image,panelSize,3,3,30,5);
    data.CropImage();*/
    //data.Mix1();
    //data.RemoveTile(9,9);
   // data.MoveTile(9,8);
   // data.MoveColumn(0,false);
    //data.MoveRow(0,true);

}

PanelGry::~PanelGry(){
    //(*Destroy(ProjektFrame)
    //*)
}

void PanelGry::UpdateUI(wxUpdateUIEvent & event){
    Paint();
}

void PanelGry::Paint(){
    wxClientDC dcClient( Panel1 );
    wxBufferedDC dc(&dcClient);
    dc.Clear();
    data.Draw( &dc );
}

void PanelGry::BackClick(wxCommandEvent& event){
    _pause = false;
    PauseClick(event);
    ProjektFrame::FRAME->setState(STATE_OPTIONS);   
}


void PanelGry::PauseClick(wxCommandEvent& event){
    if(_pause)
        _buttonPause->SetLabel("Pauza");
    else
        _buttonPause->SetLabel("Kontynuuj");    
    _pause = !_pause;      
}

bool PanelGry::paused(){
    return _pause;   
}

void PanelGry::PaintEvt(wxPaintEvent& event){
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
