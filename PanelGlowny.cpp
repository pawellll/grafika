#include "PanelGlowny.h"

#include "ProjektMain.h"

BEGIN_EVENT_TABLE(PanelGlowny,wxPanel)
    EVT_BUTTON(ID_START,PanelGlowny::StartClick)
    EVT_BUTTON(ID_SCORE,PanelGlowny::ScoreClick)
    EVT_BUTTON(ID_EXIT,PanelGlowny::ExitClick)
/////eventy
END_EVENT_TABLE()


PanelGlowny::PanelGlowny (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name): wxPanel(parent,ID,pos,size,style,name){
    _buttonStart = new wxButton(this,ID_START,wxString("Zacznij grê"),wxPoint(80,100), wxSize(120,45),0,wxDefaultValidator, "START");
    _buttonScore = new wxButton(this,ID_SCORE,wxString("Punktacja"),wxPoint(250,100), wxSize(120,45),0,wxDefaultValidator, "SCORE");  
    _buttonExit = new wxButton(this,ID_EXIT,wxString("Wyjœcie"),wxPoint(420,100), wxSize(120,45),0,wxDefaultValidator, "EXIT"); 
}

PanelGlowny::~PanelGlowny(){
    
}

void PanelGlowny::StartClick(wxCommandEvent& event){
    ///prze³¹czenie na panel opcji gry    
    ProjektFrame::FRAME->setState(STATE_OPTIONS);
}
     
void PanelGlowny::ExitClick(wxCommandEvent& event){
    /// wyjœcie z gry
    ProjektFrame::FRAME->Quit();
}

void PanelGlowny::ScoreClick(wxCommandEvent& event){
    /// prze³¹czenie na panel punktacji
    ProjektFrame::FRAME->setState(STATE_SCORE);
}
 
	
