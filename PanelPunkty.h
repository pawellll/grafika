/*
    Panel w którym zostan¹ wyœwietlone poszczególne wyniki
*/

#ifndef PANEL_PUNKTY
#define PANEL_PUNKTY

#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/button.h>

class PanelPunkty : public wxPanel{
    public :
        
        PanelPunkty (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name);
        virtual ~PanelPunkty();   
        
		void StartClick(wxCommandEvent& event);     
		void ExitClick(wxCommandEvent& event);  
		void ScoreClick(wxCommandEvent& event);  
        
    private :  
        enum{
    		ID_START = 10,
            ID_EXIT = 11,
            ID_SCORE = 12
        };
        
		DECLARE_EVENT_TABLE();
    
        wxButton * _buttonStart;
        wxButton * _buttonExit;
        wxButton * _buttonScore;
            
};


#endif
