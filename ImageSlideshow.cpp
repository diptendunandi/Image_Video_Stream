// ImageSlideshow.cpp
#include "ImageSlideshow.h"

ImageSlideshow::ImageSlideshow(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1500, 1000)),
      m_currentIndex(0),
      m_isSlideShowRunning(false),
      m_timer(this) {
    // Create and initialize the timer
    m_timer.SetOwner(this);
    Bind(wxEVT_TIMER, &ImageSlideshow::OnTimer, this);
    m_timer.Start(2000); // 2-second interval

    // Create bitmap for displaying images
    m_bitmap = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    // Create buttons
        m_btnUpload = new wxButton(this, wxID_ANY, wxT("Upload Images"));
   m_btnSlideShow = new wxButton(this, wxID_ANY, wxT("Start Slideshow"));
    m_btnNext = new wxButton(this, wxID_ANY, wxT("Next"));
    m_btnPrev = new wxButton(this, wxID_ANY, wxT("Previous"));
    

    // Bind button events
    Bind(wxEVT_BUTTON, &ImageSlideshow::OnNextImage, this, m_btnNext->GetId());
    Bind(wxEVT_BUTTON, &ImageSlideshow::OnPreviousImage, this, m_btnPrev->GetId());
    Bind(wxEVT_BUTTON, &ImageSlideshow::OnSlideShow, this, m_btnSlideShow->GetId());
    Bind(wxEVT_BUTTON, &ImageSlideshow::OnUploadImages, this, m_btnUpload->GetId());

    // Create a vertical box sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    
    // Add bitmap and buttons to the sizer
    sizer->Add(m_bitmap, 1, wxEXPAND | wxALL, 5);
    sizer->Add(m_btnNext, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    sizer->Add(m_btnPrev, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    sizer->Add(m_btnSlideShow, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    sizer->Add(m_btnUpload, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    SetSizerAndFit(sizer);
}

void ImageSlideshow::OnTimer(wxTimerEvent& event) {
    if (m_isSlideShowRunning)
        ShowNextImage();
}

void ImageSlideshow::ShowNextImage() {
    if (!m_images.empty()) {
        m_currentIndex = (m_currentIndex + 1) % m_images.size();
        m_bitmap->SetBitmap(m_images[m_currentIndex]);
    }
}

void ImageSlideshow::ShowPreviousImage() {
    if (!m_images.empty()) {
        if (m_currentIndex > 0) {
            m_currentIndex--;
        } else {
            m_currentIndex = m_images.size() - 1;
        }
        m_bitmap->SetBitmap(m_images[m_currentIndex]);
    }
}

void ImageSlideshow::OnNextImage(wxCommandEvent& event) {
    ShowNextImage();
}

void ImageSlideshow::OnPreviousImage(wxCommandEvent& event) {
    ShowPreviousImage();
}

void ImageSlideshow::OnSlideShow(wxCommandEvent& event) {
    m_isSlideShowRunning = !m_isSlideShowRunning;
    if (m_isSlideShowRunning) {
        m_btnSlideShow->SetLabel(wxT("Stop Slideshow"));
    } else {
        m_btnSlideShow->SetLabel(wxT("Start Slideshow"));
    }
}

void ImageSlideshow::OnUploadImages(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Open Image Files"), "", "",
                                "Image files (*.jpg;*.png;*.jpeg)|*.jpg;*.png;*.jpeg", 
                                wxFD_MULTIPLE | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    wxArrayString fileNames;
    openFileDialog.GetPaths(fileNames);

    // Load and display each selected image
    m_images.clear();
    for (const auto& fileName : fileNames) {
        wxBitmap bmp(fileName, wxBITMAP_TYPE_ANY);
        if (bmp.IsOk())
            m_images.push_back(bmp);
    }

    // Display the first image if available
    if (!m_images.empty()) {
        m_currentIndex = 0;
        m_bitmap->SetBitmap(m_images[m_currentIndex]);
    }
}

