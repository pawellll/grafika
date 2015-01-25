/*
    Panel w kt�rym zostan� wy�wietlone poszczeg�lne wyniki
*/

#ifndef PANEL_PUNKTY
#define PANEL_PUNKTY

#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/button.h>

#include "PanelGry.h"

class PanelPunkty : public wxPanel{
    public :
        
        PanelPunkty (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name);
        virtual ~PanelPunkty();   
        
		void backClick(wxCommandEvent& event); //////przycisk powrotu do g��wnego menu
		void update(); //////wo�ane przy zako�czeniu gry (statystyki s� zapisane w statycznym obiekcie GameSubPanel::LAST_STATS - plik PanelGry.h)
        
    private :  
        enum{
            ID_BACK = 10
        };
        
		DECLARE_EVENT_TABLE();
    
        wxButton * _buttonBack;            
};


#endif
