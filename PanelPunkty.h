/*
    Panel w którym zostan¹ wyœwietlone poszczególne wyniki
*/

#ifndef PANEL_PUNKTY
#define PANEL_PUNKTY
#include <ostream>
#include <fstream>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/listctrl.h>
#include "BestScores.h"


class PanelPunkty : public wxPanel{
    public :
        
        PanelPunkty (wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name,BestScores* scores);
        virtual ~PanelPunkty();   
        void update();
		void BackClick(wxCommandEvent& event);
        
    private :
        void typeChanged(wxCommandEvent& event);
        void createTypesList();  
        void comboBoxChanged();
        enum{
            ID_BACK = 10,
            ID_TYPESLIST,
            ID_TABLE,
            ID_KEYVALUES
        };
        
		DECLARE_EVENT_TABLE();
        wxButton* _buttonBack;
        wxComboBox* _typesList;
        wxComboBox* _keyValues; 
        wxListView* _table;
        BestScores* _scores;
        
};


#endif
