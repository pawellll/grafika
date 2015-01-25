#include "PanelOpcji.h"

#include "ProjektMain.h"

BEGIN_EVENT_TABLE(PanelOpcji,wxPanel)
    EVT_BUTTON(ID_START,PanelOpcji::StartClick)
    EVT_BUTTON(ID_BACK,PanelOpcji::BackClick)
    EVT_BUTTON(ID_CONTINUE,PanelOpcji::ContinueClick)
	EVT_COMMAND_SCROLL(ID_SCROLL_SIZE,PanelOpcji::SizeScroll)
    EVT_CHOICE(ID_CHOICE2, PanelOpcji::choosedImage)
END_EVENT_TABLE()


const wxString PanelOpcji::labels [] = {"Pojedyncze elementy","Kolumny/Wiersze"};
const wxString PanelOpcji::images [] = {"obraz", "obraz2"};

PanelOpcji::PanelOpcji (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name): wxPanel(parent,ID,pos,size,style,name){
    
    _buttonStart = new wxButton(this,ID_START,wxString("Rozpocznij"),wxPoint(180,50), wxSize(120,45),0,wxDefaultValidator, "START_OPTIONS");
    _buttonBack = new wxButton(this,ID_BACK,wxString("Wróæ"),wxPoint(350,50), wxSize(120,45),0,wxDefaultValidator, "BACK_OPTIONS");
    _buttonContinue = NULL;
    _scrollSize = new wxScrollBar(this, ID_SCROLL_SIZE, wxPoint(180,200), wxSize(120,20), wxSB_HORIZONTAL, wxDefaultValidator, wxT("WxScrollBar_alpha"));
    _textScrollSize = new wxStaticText(this, ID_TEXT1, wxT("Wymiary ukladanki : 3x3"), wxPoint(20,200), wxDefaultSize, 0, wxT("WxStaticText2"));

    _scrollSize->SetScrollbar(0, 3, 6, 1,true);
	_scrollSize->Enable(true);
	_scrollSize->SetThumbPosition(0);
	
	_choiceGameType = new wxChoice(this,ID_CHOICE1,wxPoint(180,240),wxSize(200,30),2,labels,0,wxDefaultValidator,"Choice");
    _choiceGameType -> SetSelection (0);
    
    _textGameType = new wxStaticText(this, ID_TEXT2, wxT("Wybierz typ rozgrywki"), wxPoint(20,250), wxDefaultSize, 0, wxT("WxStaticText2"));

    _choiceImage = new wxChoice(this,ID_CHOICE2,wxPoint(180,300),wxSize(200,30),2,images,0,wxDefaultValidator,"Choice");
    _choiceImage -> SetSelection (0);
    _textImage = new wxStaticText(this, ID_TEXT2, wxT("Wybierz obrazek"), wxPoint(20,300), wxDefaultSize, 0, wxT("WxStaticText2"));
    
    _imgPreview = NULL;
    wxImage MyImage;    
    MyImage.AddHandler(new wxJPEGHandler); 
    wxString file;
    file = "obraz.jpg";
    if (!MyImage.LoadFile(file, wxBITMAP_TYPE_JPEG ) )
        wxLogError(wxT("Nie mo?na za3adowa obrazka"));
    else
        {
            _imgPreview = new wxBitmapButton(this,ID_ICON, wxBitmap( MyImage.Rescale(350,350) ), wxPoint(410,160), wxSize(350,350), 0, wxDefaultValidator, "WxButton2");    
   
        }    
}

PanelOpcji::~PanelOpcji(){    
}

void PanelOpcji::StartClick(wxCommandEvent& event){
    ///prze³¹czenie na panel opcji gry    
    ///stworzenie odpowiedniego obiektu PanelGry (w zale¿noœci od wybranych parametrów)
    
    if(!_buttonContinue)
        _buttonContinue = new wxButton(this,ID_CONTINUE,wxString("Dalej"),wxPoint(520,50), wxSize(120,45),0,wxDefaultValidator, "CONTINUE_OPTIONS");
    else{
            wxMessageDialog a (this,"Na pewno chcesz opuscic gre ?",wxMessageBoxCaptionStr, wxYES_NO|wxICON_QUESTION);
            if( a.ShowModal() == wxID_NO ) return;
        }
        
    wxString file;
    file = images[_choiceImage ->GetSelection ()];
    file = file + ".jpg";      
    wxImage MyImage;    
    MyImage.AddHandler(new wxJPEGHandler); 
    
    if (!MyImage.LoadFile(file, wxBITMAP_TYPE_JPEG ) )
        wxLogError(wxT("Nie mo?na za3adowa obrazka"));
    else{        
        ProjektFrame::FRAME->setGamePanel(new PanelGry(ProjektFrame::FRAME,ProjektFrame::FRAME->ID_PANEL_GRY, wxPoint(0,0), wxSize(800,600), wxTAB_TRAVERSAL, wxString("PANEL_GRY"),MyImage,3+_scrollSize->GetThumbPosition(), (_choiceImage ->GetSelection () == 0) ) );
        ProjektFrame::FRAME->setState(STATE_GAME);
        Hide();    
    }
}
     
void PanelOpcji::BackClick(wxCommandEvent& event){
    /// wyjœcie z gry
    ProjektFrame::FRAME->setState(STATE_MAIN);
}

void PanelOpcji::ContinueClick(wxCommandEvent& event){
    ProjektFrame::FRAME->setState(STATE_GAME);  
    Hide();   
}
 
void PanelOpcji::SizeScroll(wxScrollEvent& event){
    wxString str = "Wymiary ukladanki : ";
	switch(_scrollSize->GetThumbPosition()){
        case 0: {str = str + "3x3";break;}
        case 1: {str = str + "4x4";break;}
        case 2: {str = str + "5x5";break;}
        case 3: {str = str + "6x6";break;}
    }
	_textScrollSize->SetLabel(str);
}	

void PanelOpcji::choosedImage(wxCommandEvent& event){    
    wxString file;
    file = images[_choiceImage ->GetSelection ()];
    file = file + ".jpg";      
    wxImage MyImage;    
    MyImage.AddHandler(new wxJPEGHandler); 
    
    if (!MyImage.LoadFile(file, wxBITMAP_TYPE_JPEG ) )
        wxLogError(wxT("Nie mo?na za3adowa obrazka"));
    else{
        if(_imgPreview) delete _imgPreview;
        _imgPreview = new wxBitmapButton(this,ID_ICON, wxBitmap( MyImage.Rescale(350,350) ), wxPoint(410,160), wxSize(350,350), 0, wxDefaultValidator, "WxButton2");    
    }  
}


