// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "MyImage.hpp"
#include <time.h>
#include "MyThresholdDialog.hpp"
#include "MyRotateDialog.hpp"
#include "MyHistogram.hpp"


class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};


class MyPanel: public wxPanel
{
public:
    MyPanel( wxWindow *parent ) ;
    ~MyPanel() ;
    void OpenImage(wxString fileName);
    void OnPaint(wxPaintEvent &WXUNUSED(event));
    void MirrorImage(bool horizontal);
    void BlurImage();
    void RotationImage(int id);
    void NegativeImage();
    void ThresholdImage();
    void RotateImage();
    MyImage* getImagePtr();
private:
    MyImage *m_image ;		// used to load and process the image
    wxBitmap m_bitmap ;	// used to display the image
    int m_width;
    int m_height;
};


class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    MyPanel *m_panel; // the panel inside the main frame
    void OnProcessImage(wxCommandEvent& event);
	void OnHello(wxCommandEvent& event);
	void OnOpenImage(wxCommandEvent& event);
	void OnSaveImage(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnEnCours(wxCommandEvent& event);
	void OnLarge(wxCommandEvent& event);
};



enum
{
	ID_Hello = 1,
	ID_About ,
	ID_EnCours ,
	ID_PlusLarge ,
	ID_MoinsLarge ,
	ID_Open ,
	ID_Save ,
	ID_MiroirHorizontal ,
	ID_MiroirVertical ,
	ID_Blur ,
	ID_RotationPlus90 ,
	ID_RotationMoins90 ,
	ID_Rotation180 ,
	ID_Negative ,
	ID_Desaturate ,
	ID_Threshold ,
	ID_Posterize ,
	ID_Rotation ,
	ID_NombreCouleurs ,
	ID_Contrast ,
	ID_Dither
};



IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
	MyFrame *frame = new MyFrame( wxT("munier_adli_sajkiewicz"), wxPoint(50, 50), wxSize(450, 340) );
	frame->Show( true );
	return true;
}


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    this->m_panel = new MyPanel(this);
    wxFrame::Centre(wxBOTH);
    wxStatusBar *statusBar = CreateStatusBar(1,wxSTB_DEFAULT_STYLE,0,"SatusBar");
    SetStatusText(wxT("La barre de status fonctionne très simplement !!!"));


	wxMenu *menuFile = new wxMenu ;
	wxMenu *menuProcess = new wxMenu;
	wxMenu *menuHelp = new wxMenu ;


	menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H")) ; // raccourci ctrl H
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;

	menuFile->Append(ID_Open, wxT("Open...\tCtrl-O")) ; // raccourci ctrl + O pour ouvrir
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, ID_Open) ;

	menuFile->Append(ID_Save, wxT("Save...\tCtrl-S")) ; // raccourci ctrl + S pour sauvergarder
	Bind(wxEVT_MENU, &MyFrame::OnSaveImage, this, ID_Save) ;

	menuFile->Append(ID_PlusLarge, wxT("Plus Large\tCtrl-+")); //racourci ctrl + + pour agrandir  la frame
	Bind(wxEVT_MENU, &MyFrame::OnLarge, this, ID_PlusLarge);

	menuFile->Append(ID_MoinsLarge, wxT("Moins Large\tCtrl--")); // raccourci ctrl + - pour rétrecir la frame
	Bind(wxEVT_MENU, &MyFrame::OnLarge, this, ID_MoinsLarge);

	menuFile->Append(ID_About, wxT("About..\tCtrl-?")); // raccourci pour ctrl + ? pour about
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, ID_About);

	menuFile->Append(wxID_EXIT) ;
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;


	menuProcess->Append(ID_MiroirHorizontal,wxT("Horizontal Mirror"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MiroirHorizontal);

	menuProcess->Append(ID_MiroirVertical,wxT("Vertical Mirror"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MiroirVertical);

	menuProcess->Append(ID_Blur,wxT("Blur"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Blur);

	menuProcess->Append(ID_RotationPlus90,wxT("Rotation +90"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_RotationPlus90);

	menuProcess->Append(ID_RotationMoins90,wxT("Rotation -90"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_RotationMoins90);

	menuProcess->Append(ID_Rotation180,wxT("Rotation 180"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Rotation180);

	menuProcess->Append(ID_Negative,wxT("Negative"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Negative);

	menuProcess->Append(ID_Desaturate,wxT("Desaturate"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Desaturate);

	menuProcess->Append(ID_Threshold,wxT("Threshold"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Threshold);

	menuProcess->Append(ID_Posterize,wxT("Posterize"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Posterize);

	menuProcess->Append(ID_Rotation,wxT("Rotation"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Rotation);

	menuProcess->Append(ID_NombreCouleurs,wxT("Colors Number...\tCtrl-C")); // raccourcis ctrl -C pour le nombre de couleurs
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_NombreCouleurs);

	menuProcess->Append(ID_Contrast,wxT("Contrast"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Contrast);

	menuProcess->Append(ID_Dither,wxT("Dither...\tCtrl-D")); // raccourci ctrl -D pour dithering
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage,this,ID_Dither);


	menuHelp->Append(ID_EnCours, wxT("En Cours"));
	Bind(wxEVT_MENU, &MyFrame::OnEnCours, this, ID_EnCours);


	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append( menuFile, wxT("File" )) ;
	menuBar->Append( menuHelp, wxT("Help" )) ;
	menuBar->Append(menuProcess, wxT("Process"));
	SetMenuBar(menuBar) ;
	SetStatusBar(statusBar);
}


void MyFrame::OnProcessImage(wxCommandEvent& event){
    switch (event.GetId()){
    case ID_MiroirHorizontal:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->MirrorImage(true);
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_MiroirVertical:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->MirrorImage(false);
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Blur:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->BlurImage();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_RotationPlus90:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->RotationImage(event.GetId());
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_RotationMoins90:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->RotationImage(event.GetId());
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Rotation180:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->RotationImage(event.GetId());
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Negative:
        if (this->m_panel->getImagePtr()!=nullptr){
            clock_t debut = clock();
            this->m_panel->NegativeImage();
            clock_t fin = clock();
            double total = ((double)(fin-debut))/((double)CLOCKS_PER_SEC);
            this->SetStatusText(wxT("Temps d'éxecution : ")+wxString::Format(wxT("%lf"),total)+wxT(" secondes"));

        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Desaturate:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->getImagePtr()->Desaturate();
            Refresh();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Threshold:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->ThresholdImage();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Posterize:
        if (this->m_panel->getImagePtr()!=nullptr){
            m_panel->getImagePtr()->Posterize();
            Refresh();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Rotation:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->RotateImage();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_NombreCouleurs:
        if (this->m_panel->getImagePtr()!=nullptr){
            wxString message;
            message.sprintf("%i couleurs", m_panel->getImagePtr()->NombreCouleurs());
            wxLogMessage(message);
            //wxString::Format(wxT("%lf"),total)
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Contrast:
        if (this->m_panel->getImagePtr()!=nullptr){
                MyHistogram* histo = new MyHistogram(m_panel->getImagePtr());
                int min, max;
                histo->GetBorderValues(&min,&max);
                m_panel->getImagePtr()->EnhenceContrast(min,max);
                Refresh();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Dither :
        if ( this->m_panel->getImagePtr() != nullptr) {
             this->m_panel->getImagePtr()->Dither() ;
             Refresh();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;

    default:
        break;

    }

}

void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage(wxT("Hello world from wxWidgets!"));
}

void MyFrame::OnOpenImage(wxCommandEvent& event)
{
    wxString filename = wxFileSelector("Choose a file to open");
    if (!filename.empty()){
        this->m_panel->OpenImage(filename);
    }
}

void MyFrame::OnSaveImage(wxCommandEvent& event)
{
    wxString filename = wxSaveFileSelector("", "PNG Image|*.png|BMP Image|*.bmp|JPEG Image|*.jpg", "image");
        if(filename!=wxEmptyString)

        {

                this->m_panel->getImagePtr()->SaveFile(filename);
        }
}


void MyFrame::OnLarge(wxCommandEvent& event)
{
    int width;
    int height;
    this->GetSize(&width,&height);
	if (event.GetId()==4){
        this->SetSize((width+100),height);
	}
	else this->SetSize((width-100),height);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxLogMessage(wxT("Projet Adli-Munier-Sajkiewicz 2016"));
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}

void MyFrame::OnEnCours(wxCommandEvent& event)
{
	wxLogMessage(wxT("En Construction"));
}



MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent){
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this) ;
    this->m_image = nullptr;
};

MyPanel::~MyPanel(){
    delete(this->m_image);
};

MyImage* MyPanel::getImagePtr(){
    return this->m_image;
}

void MyPanel::OpenImage(wxString fileName){
    if (this->m_image!=nullptr){

    }
    delete(this->m_image);
    //this->m_image = new MyImage(fileName, wxBITMAP_TYPE_ANY, -1);
    this->m_image = new MyImage(fileName);
    this->m_width = m_image->GetWidth();
    this->m_height = m_image->GetHeight();
    this->SetSize(this->m_width,this->m_height);
    this->GetParent()->SetClientSize(this->m_width,this->m_height);
    Refresh();
};

void MyPanel::OnPaint(wxPaintEvent &WXUNUSED(event)){
    wxPaintDC dc(this);
    //this->m_bitmap = *(new wxBitmap(*this->m_image));
    if (this->m_image!=nullptr) {
            this->m_bitmap = wxBitmap(*this->m_image);
            dc.DrawBitmap(this->m_bitmap,0,0);
    }
};

void MyPanel::MirrorImage(bool horizontal){
    this->m_image->Mirror(horizontal);
    Refresh();
}

void MyPanel::BlurImage(){
    *this->m_image = this->m_image->Blur(5);
    Refresh();
}

void MyPanel::RotationImage(int id){
    if (id==ID_RotationPlus90){
        //*this->m_image = this->m_image->Rotate90(true);
        *this->m_image = this->m_image->Rotate90();
        this->m_width = m_image->GetWidth();
        this->m_height = m_image->GetHeight();
        this->SetSize(this->m_width,this->m_height);
        this->GetParent()->SetClientSize(this->m_width,this->m_height);
    }
    else if (id==ID_RotationMoins90){
        *this->m_image = this->m_image->wxImage::Rotate90(false);
        this->m_width = m_image->GetWidth();
        this->m_height = m_image->GetHeight();
        this->SetSize(this->m_width,this->m_height);
        this->GetParent()->SetClientSize(this->m_width,this->m_height);
    }
    else *getImagePtr() = getImagePtr()->Rotate180();
    Refresh();
}

void MyPanel::NegativeImage(){
    this->m_image->Negative();
    Refresh();
}

void MyPanel::ThresholdImage(){
    MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
    dlg->ShowModal() ;
    this->m_image->Threshold(dlg->m_threshold->GetValue());
    Refresh();
}

void MyPanel::RotateImage(){
    MyRotateDialog *dlg = new MyRotateDialog(this, -1, wxDefaultPosition, wxSize(250,140));
    if (dlg->ShowModal() == wxID_OK){
        switch(dlg->RadioBox1->GetSelection()){
        case 0:
            RotationImage(ID_RotationPlus90);
            break;
        case 1:
            RotationImage(ID_Rotation180);
            break;
        case 2:
            RotationImage(ID_RotationMoins90);
            break;
        default:
            break;
        }
    }
    else dlg->Destroy();
}
