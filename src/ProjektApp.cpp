/***************************************************************
 * Name:      ProjektApp.cpp
 * Purpose:   Code for Application Class
 * Author:    p (p)
 * Created:   2015-01-20
 * Copyright: p (p)
 * License:
 **************************************************************/

#include "ProjektApp.h"

//(*AppHeaders
#include "ProjektMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ProjektApp);

bool ProjektApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ProjektFrame* Frame = new ProjektFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
