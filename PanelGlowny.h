/*
    G³ówny panel, na razie ma trzy przyciski, potem mo¿na dodaæ jakiœ bajer
*/

#ifndef PANEL_GLOWNY
#define PANEL_GLOWNY

#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/button.h>

class PanelGlowny : public wxPanel{
    public :
        
        PanelGlowny (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name);
        virtual ~PanelGlowny();   
        
		void StartClick(wxCommandEvent& event);     
		void ExitClick(wxCommandEvent& event);  
		void ScoreClick(wxCommandEvent& event);  
		
        
    private :  
        enum{
    		ID_START = 7,
            ID_EXIT = 8,
            ID_SCORE = 9
        };
        
		DECLARE_EVENT_TABLE();
    
        wxButton * _buttonStart;
        wxButton * _buttonExit;
        wxButton * _buttonScore;            
};


#endif
