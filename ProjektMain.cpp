#include "ProjektMain.h"
#include <wx/msgdlg.h>
#include <wx/intl.h>
#include <wx/string.h>

enum wxbuildinfoformat {
    short_f, long_f 
};

wxString wxbuildinfo(wxbuildinfoformat format){
    wxString wxbuild(wxVERSION_STRING);
    if (format == long_f )    {
        #if defined(__WXMSW__)
                wxbuild << _T("-Windows");
        #elif defined(__UNIX__)
                wxbuild << _T("-Linux");
        #endif
        #if wxUSE_UNICODE
                wxbuild << _T("-Unicode build");
        #else
                wxbuild << _T("-ANSI build");
        #endif // wxUSE_UNICODE
    }
    return wxbuild;
}

BEGIN_EVENT_TABLE(ProjektFrame,wxFrame)
    /////eventy
END_EVENT_TABLE()

ProjektFrame * ProjektFrame::FRAME = NULL;


ProjektFrame::ProjektFrame(wxWindow* parent,wxWindowID id){    
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(800,600));
    SetMinSize(wxSize(800,600));
    SetMaxSize(wxSize(800,600));
        
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Center();

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ProjektFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ProjektFrame::OnAbout);
    
    _mainPanel = new PanelGlowny(this,ID_PANEL_GLOWNY, wxPoint(0,0), wxSize(800,600), wxTAB_TRAVERSAL, wxString("PANEL_GRY"));
    _currentPanel = _mainPanel;
    _optionPanel = NULL;
    _scorePanel = NULL;
    _gamePanel = NULL;
    
    _currentPanel->SetMinSize(wxSize(800,600));
    _currentPanel->SetMaxSize(wxSize(800,600));
    
    FRAME = this;
}

ProjektFrame::~ProjektFrame(){
}

void ProjektFrame::OnQuit(wxCommandEvent& event){        
    Quit();
}

void ProjektFrame::OnAbout(wxCommandEvent& event){
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Cha³upy welcome to..."));
}

void ProjektFrame::setState(char state){
    _currentPanel -> Hide();
    switch (state){
        case STATE_MAIN   : {     
            if(!_mainPanel)  _mainPanel = new PanelGlowny(this,ID_PANEL_GLOWNY, wxPoint(0,0), wxSize(800,600), wxTAB_TRAVERSAL, wxString("PANEL_PUNKTY"));
            _currentPanel = _mainPanel;    
            break;
        }
        case STATE_SCORE : {
            if(!_scorePanel) _scorePanel = new PanelPunkty(this,ID_PANEL_PUNKTY, wxPoint(0,0), wxSize(800,600), wxTAB_TRAVERSAL, wxString("PANEL_PUNKTY"));
            _currentPanel = _scorePanel;
            break;
        } 
        case STATE_OPTIONS  : {
            if(!_optionPanel) _optionPanel = new PanelOpcji(this,ID_PANEL_OPCJI, wxPoint(0,0), wxSize(800,600), wxTAB_TRAVERSAL, wxString("PANEL_PUNKTY"));
            _currentPanel = _optionPanel;
            break;
        }    
        case STATE_GAME    : {
            /// prze³¹czenie na panel gry - nale¿y wczeœniej stworzyæ odpowiedni obiekt dziedzicz¹cy po PanelGry poprzez odpowiedni¹ metodê w obiekcie ProjektMain.
            if(_gamePanel) _currentPanel = _gamePanel;
            break;
        }  
    } 
    _currentPanel -> Show();    
}

void ProjektFrame::Quit(){
    Close();    
}

void ProjektFrame::setGamePanel(PanelGry * panel){
    if(_gamePanel) delete _gamePanel;    
    _gamePanel = panel;
}

void ProjektFrame::gameWon(){
    
}
