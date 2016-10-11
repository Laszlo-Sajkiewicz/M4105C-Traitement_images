#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyImage: public wxImage {
public:
    MyImage(const wxString& fileName) ;
    MyImage(wxImage image) ;
    MyImage() ;
    void Negative();
    void Desaturate();
    void Threshold(int seuil);
    void Mirror(bool horizontally);
    wxImage Rotate90();
    void Posterize();
    int NombreCouleurs();
    void EnhenceContrast(int minValue, int maxValue);
    void Dither(); // void dither tp9
};

#endif
