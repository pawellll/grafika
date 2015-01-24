#include "PanelOpcji.h"

#include "ProjektMain.h"

BEGIN_EVENT_TABLE(PanelOpcji,wxPanel)
    EVT_BUTTON(ID_START,PanelOpcji::StartClick)
    EVT_BUTTON(ID_SCORE,PanelOpcji::ScoreClick)
    EVT_BUTTON(ID_EXIT,PanelOpcji::ExitClick)
/////eventy
END_EVENT_TABLE()


PanelOpcji::PanelOpcji (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name): wxPanel(parent,ID,pos,size,style,name){
    _buttonStart = new wxButton(this,ID_START,wxString("Zacznij grê"),wxPoint(80,100), wxSize(120,45),0,wxDefaultValidator, "START");
    _buttonScore = new wxButton(this,ID_SCORE,wxString("Punktacja"),wxPoint(250,100), wxSize(120,45),0,wxDefaultValidator, "SCORE");  
    _buttonExit = new wxButton(this,ID_EXIT,wxString("Wyjœcie"),wxPoint(420,100), wxSize(120,45),0,wxDefaultValidator, "EXIT"); 
}

PanelOpcji::~PanelOpcji(){
    
}

void PanelOpcji::StartClick(wxCommandEvent& event){
    ///prze³¹czenie na panel opcji gry    
    ProjektFrame::FRAME->setState(STATE_OPTIONS);
}
     
void PanelOpcji::ExitClick(wxCommandEvent& event){
    /// wyjœcie z gry
    ProjektFrame::FRAME->Quit();
}

void PanelOpcji::ScoreClick(wxCommandEvent& event){
    /// prze³¹czenie na panel punktacji
    ProjektFrame::FRAME->setState(STATE_SCORE);
}
 
	
