/***************************************************************
 * Name:      ProjektMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    p (p)
 * Created:   2015-01-20
 * Copyright: p (p)
 * License:
 **************************************************************/

#include "ProjektMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(ProjektFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
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

//(*IdInit(ProjektFrame)
const long ProjektFrame::ID_PANEL1 = wxNewId();
const long ProjektFrame::idMenuQuit = wxNewId();
const long ProjektFrame::idMenuAbout = wxNewId();
const long ProjektFrame::ID_STATUSBAR1 = wxNewId();
//*)
//const long ProjektFrame::TIMER_ID = wxNewId();

BEGIN_EVENT_TABLE(ProjektFrame,wxFrame)
    //(*EventTable(ProjektFrame)
    //*)
    EVT_UPDATE_UI(ID_PANEL1, ProjektFrame::UpdateUI)
    //EVT_PAINT(ProjektFrame::PaintEvt)
    //EVT_TIMER(TIMER_ID, ProjektFrame::OnTimer)
END_EVENT_TABLE()

ProjektFrame::ProjektFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ProjektFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(600,600));
    SetMinSize(wxSize(600,600));
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(600,600), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(600,600));
    Panel1->SetMaxSize(wxSize(600,600));
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
    //*)
    wxImageHandler * pngLoader = new wxJPEGHandler();
    wxImage::AddHandler(pngLoader);

    image.LoadFile("obraz.jpg",wxBITMAP_TYPE_JPEG );
    if (image.IsOk())
        SetTitle("ok");
    wxSize panelSize = Panel1->GetSize();
    data = PuzzleData(&image,panelSize,3,3,30,5);
    data.CropImage();
    //data.Mix1();
    //data.RemoveTile(9,9);
   // data.MoveTile(9,8);
   // data.MoveColumn(0,false);
    //data.MoveRow(0,true);

}

ProjektFrame::~ProjektFrame()
{
    //(*Destroy(ProjektFrame)
    //*)
}

void ProjektFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ProjektFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void ProjektFrame::UpdateUI(wxUpdateUIEvent & event)
{
    Paint();
}

void ProjektFrame::Paint()
{
    wxClientDC dcClient( Panel1 );
    wxBufferedDC dc(&dcClient);
    dc.Clear();
    data.Draw( &dc );
}

void ProjektFrame::PaintEvt(wxPaintEvent& event)
{
    /*wxPaintDC dc(this);
    std::cout<<"print\n";
    //dc.Clear();
    //data.Draw(&dc);
    dc.DrawRotatedText("MY ROTATED TEXT...",200,200,3);
    if ( data.GetIsAnimated())
    {

        data.ProccessAnim(1);
        data.DrawTileAnim(&dc);
    } else {
        data.Draw(&dc);
    }*/
}

/*void ProjektFrame::OnTimer(wxTimerEvent& event)
{

}*/
