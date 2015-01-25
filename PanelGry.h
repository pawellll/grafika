/*
    Dawne ProjektMain, panel, w którym bêdzie wyœwietlana uk³adanka 
*/

#ifndef PANEL_GRY
#define PANEL_GRY

#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/image.h>
#include <wx/event.h>
#include <wx/msgdlg.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bmpbuttn.h>

#include "PuzzleData.h"

class GameSubPanel : public wxPanel{
    public:
        GameSubPanel(wxWindow * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name, wxImage & img, int gameSize, bool gameType);
        virtual ~GameSubPanel();
        
        void mouseDown(wxMouseEvent& event);
        void mouseUp(wxMouseEvent& event);
        void paint();
        void updateUI(wxUpdateUIEvent& event);
        void paintEvt(wxPaintEvent& event);
        
    private:
        
        int _tiles,_lastX,_lastY;
        bool _type;
        DECLARE_EVENT_TABLE()
        
        PuzzleData data;
        wxImage image;
};
    
class PanelGry : public wxPanel{
    public :    
        
        PanelGry(wxWindow * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name, wxImage img, int gameSize, bool gameType);
        virtual ~PanelGry();
        
        bool paused();
        
    private:
    
        enum {
            ID_BACK = 0,
            ID_PANEL1 = 1,
            ID_TIMER = 2,
            ID_PAUSE = 3,
            ID_ICON = 4
        };		
		
        void paint();
        void updateUI(wxUpdateUIEvent& event);
        void paintEvt(wxPaintEvent& event);
        void backClick(wxCommandEvent& event);
        void pauseClick(wxCommandEvent& event);
        void keyDown(wxKeyEvent& event);
        void keyUp(wxKeyEvent& event);
        
       // void OnTimer(wxTimerEvent& event);

        bool _pause;
        GameSubPanel* _panel1;
        wxButton * _buttonBack;         
        wxButton * _buttonPause;  
        wxBitmapButton * _imagePreview; 

        DECLARE_EVENT_TABLE()
        
        wxImage image;
        //wxBufferedDC dc;
};

#endif  ////// PANEL_GRY
