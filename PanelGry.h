/*
    Dawne ProjektMain, panel, w którym bêdzie wyœwietlana uk³adanka 
*/

#ifndef PANEL_GRY
#define PANEL_GRY

#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statusbr.h>

#include "PuzzleData.h"
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/image.h>

class PanelGry : public wxPanel{
    public :    
        
        PanelGry(wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name) ;
        virtual ~PanelGry();
        
    private:

        void Paint();
        void UpdateUI(wxUpdateUIEvent& event);
        void PaintEvt(wxPaintEvent& event);
       // void OnTimer(wxTimerEvent& event);

        //(*Handlers(ProjektFrame)
        //void OnQuit(wxCommandEvent& event);
        //void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(ProjektFrame)
        static const long ID_PANEL1;
        //static const long idMenuQuit;
        //static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ProjektFrame)
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
        
        PuzzleData data;
        wxImage image;
        //wxBufferedDC dc;
};


#endif  ////// PANEL_GRY
