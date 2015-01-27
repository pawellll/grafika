#include "PanelPunkty.h"
#include "ProjektMain.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>


BEGIN_EVENT_TABLE(PanelPunkty,wxPanel)
    EVT_BUTTON(ID_BACK,PanelPunkty::BackClick)
    EVT_COMBOBOX(ID_TYPESLIST, PanelPunkty::typeChanged)
    EVT_COMBOBOX(ID_KEYVALUES, PanelPunkty::typeChanged)
END_EVENT_TABLE()

std::string typesNames[8]{
    "Typ 1 Rozmiar: 3x3",
    "Typ 1 Rozmiar: 4x4",
    "Typ 1 Rozmiar: 5x5",
    "Typ 1 Rozmiar: 6x6",
    
    "Typ 2 Rozmiar: 3x3",
    "Typ 2 Rozmiar: 4x4",
    "Typ 2 Rozmiar: 5x5",
    "Typ 2 Rozmiar: 6x6",
};

PanelPunkty::PanelPunkty(wxFrame * parent, wxWindowID ID, wxPoint pos, wxSize size, long style, const wxString &name,BestScores* scores): 
    wxPanel(parent,ID,pos,size,style,name),
    _scores(scores)
{
    SetAutoLayout(true);
    
  
    // initialize all controls and table
    createTypesList();
    _buttonBack = new wxButton(this,ID_BACK,wxString("Wróæ"),wxPoint(5,55), wxSize(220,25), 0, wxDefaultValidator, wxT("WxButton1"));
    _table = new wxListView(this,ID_TABLE,wxPoint(350,5),wxSize(400,400));
    _table->InsertColumn(0,"l.p."); 
    _table->InsertColumn(1,"Nick"); 
    _table->InsertColumn(2,"Czas"); 
    _table->InsertColumn(3,"Liczba ruchów"); 
    _table->SetColumnWidth(0,30);
    _table->SetColumnWidth(1,100);
    _table->SetColumnWidth(2,100);
    _table->SetColumnWidth(3,100);
}   




PanelPunkty::~PanelPunkty(){     
}

void PanelPunkty::BackClick(wxCommandEvent& event){
    ///prze³¹czenie na panel opcji gry    
    ProjektFrame::FRAME->setState(STATE_MAIN);
}

void PanelPunkty::createTypesList(){
    _typesList = new wxComboBox(this,ID_TYPESLIST,"Wybierz rodzaj gry",wxPoint(5,30), wxSize(220,25));
    for(int i=0; i!=8; ++i){
        _typesList->Append(typesNames[i]);
    }    
    _keyValues = new wxComboBox(this,ID_KEYVALUES,"Wybierz rodzaj najlepszych wyników",wxPoint(5,5), wxSize(220,25));
    _keyValues->Append("Najlepsze wyniki wg czasu");
    _keyValues->Append("Najlepsze wyniki wg liczby ruchów");
    _keyValues->SetSelection(0);
}


/*
    unsigned int time;
    unsigned int moves;
    short int level;
    bool gameType;   
*/

void PanelPunkty::update(){
    int gameTypeEnum = 0;
    int time = GameSubPanel::LAST_STATS.time;
    int moves = GameSubPanel::LAST_STATS.moves;
    int level = GameSubPanel::LAST_STATS.level; // wymiar 3-> 3x3
    gameTypeEnum += level-3;
    
    bool gameType = GameSubPanel::LAST_STATS.gameType; // true - zwyk³a gra, flase - przesuwanie kolumn, wierszy
    if(!gameType){
        gameTypeEnum+=4;
    }
    
    bool isBestMoves;
    bool isBestTime;
    isBestMoves = _scores->isBestScore(time,moves,static_cast<GameTypesEnum>(gameTypeEnum));
    isBestTime = _scores->isBestScore(time,moves,static_cast<GameTypesEnum>(gameTypeEnum+8));
    if(isBestMoves || isBestTime){
        int selection=level-3;
        if(!gameType){
            selection+=4;
        }
        _typesList->SetSelection(selection);
        if(isBestMoves){
            wxMessageBox ("Gratulacje, Twój wynik zalicza siê do najlepszych pod wzglêdem liczby ruchów!","Najlepszy wynik!",wxOK|wxCENTRE,this);
            _keyValues->SetSelection(1); 
        }
        if(isBestTime){
            wxMessageBox ("Gratulacje, Twój wynik zalicza siê do najlepszych pod wzglêdem czasu!","Najlepszy wynik!",wxOK|wxCENTRE,this);
            _keyValues->SetSelection(0); 
        }
        
        wxString nick;
        nick = wxGetTextFromUser("Podaj swój nick","Podaj swój nick","nick",this);
        if(isBestMoves){
             _scores->addScore(nick.ToStdString(),time,moves,static_cast<GameTypesEnum>(gameTypeEnum+8));
        }
        if(isBestTime){
            _scores->addScore(nick.ToStdString(),time,moves,static_cast<GameTypesEnum>(gameTypeEnum));
        }
        comboBoxChanged();
    }
}

void PanelPunkty::typeChanged(wxCommandEvent& event){
    comboBoxChanged();    
}

void PanelPunkty::comboBoxChanged(){
    if(_typesList->GetSelection()==wxNOT_FOUND){
        return;
    }
    GameTypesEnum type = static_cast<GameTypesEnum>(_typesList->GetSelection());
    int k = _keyValues->GetSelection();
    k *=8;
    std::list<BestScores::score>* scores = _scores->getScores(static_cast<GameTypesEnum>(static_cast<int>(type)+k));
    _table->DeleteAllItems(); 	
    std::list<BestScores::score>::const_reverse_iterator i;
    int j=scores->size();
    for(i=scores->crbegin();i!=scores->crend();++i,--j){
        std::ostringstream s1,s2,s3;
        s1 << j;
        int time = std::get<BestScores::TIME>(*i);
        s2<<time;
        int moves = std::get<BestScores::MOVES>(*i);
        s3<<moves;
        long index=_table->InsertItem(0,s1.str());
        _table->SetItem(index,1,std::get<BestScores::NAME>(*i));
        _table->SetItem(index,2,s2.str());
        _table->SetItem(index,3,s3.str());
    }
}
	
