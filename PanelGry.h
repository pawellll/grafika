/*
    Dawne ProjektMain, panel, w którym bêdzie wyœwietlana uk³adanka 
*/

#ifndef PANEL_GRY
#define PANEL_GRY

#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
#include <wx/button.h>

#include "PuzzleData.h"
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/image.h>

class PanelGry : public wxPanel{
    public :    
        
        PanelGry(wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name) ;
        virtual ~PanelGry();
        
        bool paused();
        
    private:
    
        enum {
            ID_BACK = 0,
            ID_PANEL1 = 1,
            ID_TIMER = 2,
            ID_PAUSE = 3
        };		
		
        void Paint();
        void UpdateUI(wxUpdateUIEvent& event);
        void PaintEvt(wxPaintEvent& event);
        void BackClick(wxCommandEvent& event);
        void PauseClick(wxCommandEvent& event);
        
       // void OnTimer(wxTimerEvent& event);

        bool _pause;
        wxPanel* Panel1;
        wxButton * _buttonBack;         
        wxButton * _buttonPause;   

        DECLARE_EVENT_TABLE()
        
        PuzzleData data;
        wxImage image;
        //wxBufferedDC dc;
};

#endif  ////// PANEL_GRY
