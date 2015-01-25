#include "PanelPunkty.h"

#include "ProjektMain.h"

BEGIN_EVENT_TABLE(PanelPunkty,wxPanel)
    EVT_BUTTON(ID_BACK,PanelPunkty::backClick)
END_EVENT_TABLE()


PanelPunkty::PanelPunkty (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name): wxPanel(parent,ID,pos,size,style,name){
    _buttonBack = new wxButton(this,ID_BACK,wxString("Wróæ"),wxPoint(80,100), wxSize(120,45),0,wxDefaultValidator, "SCORE_BACK");
}

PanelPunkty::~PanelPunkty(){    
}

void PanelPunkty::backClick(wxCommandEvent& event){
    ///prze³¹czenie na panel opcji gry    
    ProjektFrame::FRAME->setState(STATE_MAIN);
}

void PanelPunkty::update(){
    
}
	
