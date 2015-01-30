#include "PanelGlowny.h"

#include "ProjektMain.h"

BEGIN_EVENT_TABLE(MainPanel,wxPanel)
    EVT_BUTTON(ID_START,MainPanel::StartClick)
    EVT_BUTTON(ID_SCORE,MainPanel::ScoreClick)
    EVT_BUTTON(ID_EXIT,MainPanel::ExitClick)
/////eventy
END_EVENT_TABLE()


MainPanel::MainPanel (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name): wxPanel(parent,ID,pos,size,style,name){
    _buttonStart = new wxButton(this,ID_START,wxString("Nowa Gra"),wxPoint(180,100), wxSize(120,45),0,wxDefaultValidator, "START");
    _buttonScore = new wxButton(this,ID_SCORE,wxString("Punktacja"),wxPoint(350,100), wxSize(120,45),0,wxDefaultValidator, "SCORE");  
    _buttonExit = new wxButton(this,ID_EXIT,wxString("Wyjœcie"),wxPoint(520,100), wxSize(120,45),0,wxDefaultValidator, "EXIT"); 
}

MainPanel::~MainPanel(){
    
}

void MainPanel::StartClick(wxCommandEvent& event){
    ///prze³¹czenie na panel opcji gry    
    ProjektFrame::FRAME->setState(STATE_OPTIONS);
}
     
void MainPanel::ExitClick(wxCommandEvent& event){
    /// wyjœcie z gry
    ProjektFrame::FRAME->Quit();
}

void MainPanel::ScoreClick(wxCommandEvent& event){
    /// prze³¹czenie na panel punktacji
    ProjektFrame::FRAME->setState(STATE_SCORE);
}
	
