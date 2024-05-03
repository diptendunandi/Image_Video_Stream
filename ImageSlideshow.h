// ImageSlideshow.h
#ifndef IMAGESLIDESHOW_H
#define IMAGESLIDESHOW_H

#include <wx/wx.h>
#include <vector>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include <wx/timer.h>

class ImageSlideshow : public wxFrame {
public:
    ImageSlideshow(const wxString& title);
    
private:
    void OnTimer(wxTimerEvent& event);
    void ShowNextImage();
    void ShowPreviousImage();
    void OnNextImage(wxCommandEvent& event);
    void OnPreviousImage(wxCommandEvent& event);
    void OnSlideShow(wxCommandEvent& event);
    void OnUploadImages(wxCommandEvent& event);

    void ScaleAndSetBitmap(const wxBitmap& bmp); // Declaration of ScaleAndSetBitmap

    std::vector<wxBitmap> m_images;
    size_t m_currentIndex;
    bool m_isSlideShowRunning;
    wxStaticBitmap* m_bitmap;
    wxTimer m_timer;
    wxButton* m_btnNext;
    wxButton* m_btnPrev;
    wxButton* m_btnSlideShow;
    wxButton* m_btnUpload;
};

class MyApp1 : public wxApp {
public:
    virtual bool OnInit() override;
};

#endif // IMAGESLIDESHOW_H