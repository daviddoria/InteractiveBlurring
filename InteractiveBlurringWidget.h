#ifndef InteractiveBlurringWidget_H
#define InteractiveBlurringWidget_H

#include "ui_InteractiveBlurringWidget.h"

// ITK
#include "itkVectorImage.h"

// Qt
#include <QMainWindow>

class InteractiveBlurringWidget : public QMainWindow, public Ui::InteractiveBlurringWidget
{
  Q_OBJECT
public:
  typedef itk::VectorImage<unsigned char,2> ImageType;

  // Constructor/Destructor
  InteractiveBlurringWidget();
  ~InteractiveBlurringWidget() {};

public slots:
  // Menus
  void on_actionOpen_activated();
  void on_actionSave_activated();

  void on_sldBlurKernelVariance_valueChanged(float);

protected:

  ImageType::Pointer Image;
  ImageType::Pointer BlurredImage;

};

#endif // InteractiveBlurringWidget_H
