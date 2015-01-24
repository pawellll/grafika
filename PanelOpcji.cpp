#include "PanelOpcji.h"

#include "ProjektMain.h"

BEGIN_EVENT_TABLE(PanelOpcji,wxPanel)
    EVT_BUTTON(ID_START,PanelOpcji::StartClick)
    EVT_BUTTON(ID_BACK,PanelOpcji::BackClick)
    EVT_BUTTON(ID_CONTINUE,PanelOpcji::ContinueClick)
END_EVENT_TABLE()


PanelOpcji::PanelOpcji (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name): wxPanel(parent,ID,pos,size,style,name){
    _buttonStart = new wxButton(this,ID_START,wxString("Rozpocznij"),wxPoint(180,100), wxSize(120,45),0,wxDefaultValidator, "START_OPTIONS");
    _buttonBack = new wxButton(this,ID_BACK,wxString("Wróæ"),wxPoint(350,100), wxSize(120,45),0,wxDefaultValidator, "BACK_OPTIONS");
    _buttonContinue = NULL;
}

PanelOpcji::~PanelOpcji(){    
}

void PanelOpcji::StartClick(wxCommandEvent& event){
    ///prze³¹czenie na panel opcji gry    
    ///stworzenie odpowiedniego obiektu PanelGry (w zale¿noœci od wybranych parametrów)
    if(!_buttonContinue)
        _buttonContinue = new wxButton(this,ID_CONTINUE,wxString("Dalej"),wxPoint(520,100), wxSize(120,45),0,wxDefaultValidator, "CONTINUE_OPTIONS");
    ProjektFrame::FRAME->setGamePanel(new PanelGry(ProjektFrame::FRAME,ProjektFrame::FRAME->ID_PANEL_GRY, wxPoint(0,0), wxSize(800,600), wxTAB_TRAVERSAL, wxString("PANEL_GRY") ) );
    ProjektFrame::FRAME->setState(STATE_GAME);
    Hide();
}
     
void PanelOpcji::BackClick(wxCommandEvent& event){
    /// wyjœcie z gry
    ProjektFrame::FRAME->setState(STATE_MAIN);
}

void PanelOpcji::ContinueClick(wxCommandEvent& event){
    ProjektFrame::FRAME->setState(STATE_GAME);    
}
 
	
