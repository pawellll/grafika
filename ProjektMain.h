/***************************************************************
 * Name:      ProjektMain.h
 * Purpose:   Defines Application Frame
 * Author:    p (p)
 * Created:   2015-01-20
 * Copyright: p (p)
 * License:
 **************************************************************/

#ifndef PROJEKTMAIN_H
#define PROJEKTMAIN_H

//(*Headers(ProjektFrame)
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)
#include "PuzzleData.h"
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/image.h>

class ProjektFrame: public wxFrame
{
    public:

        ProjektFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ProjektFrame();

    private:

     void Paint();
        void UpdateUI(wxUpdateUIEvent& event);
        void PaintEvt(wxPaintEvent& event);
       // void OnTimer(wxTimerEvent& event);

        //(*Handlers(ProjektFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(ProjektFrame)
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
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

#endif // PROJEKTMAIN_H
