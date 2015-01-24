/*
    Panel w którym gracz wybiera rodzaj gry, parametry itd itd
*/

#ifndef PANEL_OPCJI
#define PANEL_OPCJI

#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/button.h>

class PanelOpcji : public wxPanel{
    public :
        
        PanelOpcji (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name);
        virtual ~PanelOpcji();   
        
		void StartClick(wxCommandEvent& event);     
		void ExitClick(wxCommandEvent& event);  
		void ScoreClick(wxCommandEvent& event);  
        
    private :  
        enum{
    		ID_START = 13,
            ID_EXIT = 14,
            ID_SCORE = 15
        };
        
		DECLARE_EVENT_TABLE();
    
        wxButton * _buttonStart;
        wxButton * _buttonExit;
        wxButton * _buttonScore;
            
};


#endif
