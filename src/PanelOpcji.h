/*
    Panel w którym gracz wybiera rodzaj gry, parametry itd itd
*/

#ifndef PANEL_OPCJI
#define PANEL_OPCJI

#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/scrolbar.h>
#include <wx/choice.h>
#include <wx/msgdlg.h>
#include <wx/image.h>
#include <wx/bmpbuttn.h>

class OptionsPanel : public wxPanel{
    public :
        
        OptionsPanel (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name);
        virtual ~OptionsPanel();   
        
		void StartClick(wxCommandEvent& event);     
		void BackClick(wxCommandEvent& event);
		void ContinueClick(wxCommandEvent& event);
		void SizeScroll(wxScrollEvent& event);
		void choosedImage(wxCommandEvent& event);
		void onCurrentPanel(bool current);
        
    private :  
        static const wxString labels [];
        static const wxString images [];
        
        enum{
    		ID_START = 13,
            ID_BACK = 14,
            ID_CONTINUE = 15,
            ID_TEXT1 = 16,
            ID_SCROLL_SIZE = 17,
            ID_TEXT2 = 18,
            ID_CHOICE1 = 19,
            ID_CHOICE2 = 20,
            ID_TEXT3 = 21,
            ID_PREVIEW = 22,
            ID_ICON = 23
        };
        
		DECLARE_EVENT_TABLE();
    
        wxButton * _buttonStart;
        wxButton * _buttonBack;
        wxButton * _buttonContinue;
                
        wxScrollBar * _scrollSize;
        wxStaticText * _textScrollSize;
        wxChoice * _choiceGameType;
        wxStaticText * _textGameType;
        wxChoice * _choiceImage;
        wxStaticText * _textImage;
        wxBitmapButton * _imgPreview;   
};


#endif
