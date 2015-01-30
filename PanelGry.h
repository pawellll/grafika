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

class GamePanel;

class GameStats{
    public :
        GameStats(int LEVEL, bool GAMETYPE){time = 0; moves =0; level=LEVEL; gameType = GAMETYPE;}
        unsigned int time;
        unsigned int moves;
        short int level;
        bool gameType;    
};

class GameSubPanel : public wxPanel{
    public:
        GameSubPanel(wxWindow * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name, wxImage & img, int gameSize, bool gameType);
        virtual ~GameSubPanel();
        
        void mouseDown(wxMouseEvent& event);
        void mouseUp(wxMouseEvent& event);
        void paint();
        void updateUI(wxUpdateUIEvent& event);
        void paintEvt(wxPaintEvent& event);
        bool gameEnd(){return _end;}
        
        static GameStats LAST_STATS;
        
        unsigned int _moves;
        
    private:
        
        void gameFinished();
        int _tiles,_lastX,_lastY;
        bool _type,_end;
        DECLARE_EVENT_TABLE()
        
        PuzzleData data;
        wxImage image;
};
    
class GamePanel : public wxPanel{
    public :    
        
        GamePanel(wxWindow * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name, wxImage img, int gameSize, bool gameType);
        virtual ~GamePanel();
        
        bool paused();
		
        void paint();
        void updateUI(wxUpdateUIEvent& event);
        void backClick(wxCommandEvent& event);
        void pauseClick(wxCommandEvent& event);
        void keyDown(wxKeyEvent& event);
        void keyUp(wxKeyEvent& event);
        void mouseUp(wxMouseEvent& event){_panel1 -> mouseUp(event);}
        void OnTimer(wxTimerEvent& event);
        unsigned int getTime(){return _time;}
        
    private:
    
        enum {
            ID_BACK = 0,
            ID_PANEL1 = 1,
            ID_TIMER = 666,
            ID_PAUSE = 3,
            ID_ICON = 4,
            ID_TEXT1 = 5,
            ID_TEXT2 = 6
        };		
        
        unsigned int _moves;
        unsigned int _time;
        bool _pause;
        GameSubPanel* _panel1;
        wxButton * _buttonBack;         
        wxButton * _buttonPause;  
        wxBitmapButton * _imagePreview; 
        wxStaticText * _textTime;
        wxStaticText * _textMoves;
        wxTimer * _timer;

        DECLARE_EVENT_TABLE()
        
        wxImage image;
        //wxBufferedDC dc;
};

#endif  ////// PANEL_GRY
