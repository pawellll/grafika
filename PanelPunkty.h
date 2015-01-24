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
        
		void BackClick(wxCommandEvent& event);
        
    private :  
        enum{
            ID_BACK = 10
        };
        
		DECLARE_EVENT_TABLE();
    
        wxButton * _buttonBack;            
};


#endif
