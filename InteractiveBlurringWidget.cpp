#include "InteractiveBlurringWidget.h"

// ITK
#include "itkCastImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkSmoothingRecursiveGaussianImageFilter.h"

// Qt
#include <QFileDialog>
#include <QGraphicsPixmapItem>

// Submodules
#include "ITKQtHelpers/ITKQtHelpers.h"

// Constructor
InteractiveBlurringWidget::InteractiveBlurringWidget()
{
  this->setupUi(this);

  this->OriginalScene = new QGraphicsScene;
  this->gfxviewOriginal->setScene(this->OriginalScene);
  
  this->BlurredScene = new QGraphicsScene;
  this->gfxviewBlurred->setScene(this->BlurredScene);

  // Setup toolbar
  QIcon openIcon = QIcon::fromTheme("document-open");
  actionOpen->setIcon(openIcon);
  this->toolBar->addAction(actionOpen);
  
  QIcon saveIcon = QIcon::fromTheme("document-save");
  actionSave->setIcon(saveIcon);
  this->toolBar->addAction(actionSave);
};

void InteractiveBlurringWidget::on_actionOpen_activated()
{
  // Get a filename to open
  QString fileName = QFileDialog::getOpenFileName(this, "Open File", ".", "Image Files (*.png *.mhd *.tif)");

  std::cout << "Got filename: " << fileName.toStdString() << std::endl;
  if(fileName.toStdString().empty())
    {
    std::cout << "Filename was empty." << std::endl;
    return;
    }

  typedef itk::ImageFileReader<ImageType> ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(fileName.toStdString());
  reader->Update();

  this->Image = reader->GetOutput();

  QPixmap pixmap;
  pixmap.convertFromImage(ITKQtHelpers::GetQImageColor(this->Image.GetPointer()));
  QGraphicsPixmapItem* pixmapItem = this->OriginalScene->addPixmap(pixmap);

  this->gfxviewOriginal->fitInView(pixmapItem);
}

void InteractiveBlurringWidget::on_actionSave_activated()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Save File", ".", "Image Files (*.mhd)");
  std::cout << "Got filename: " << fileName.toStdString() << std::endl;

  if(fileName.toStdString().empty())
    {
    std::cout << "Filename was empty." << std::endl;
    return;
    }

  typedef  itk::ImageFileWriter<ImageType> WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(fileName.toStdString());
  writer->SetInput(this->BlurredImage);
  writer->Update();
}

void InteractiveBlurringWidget::on_sldBlurKernelVariance_valueChanged(float value)
{
  typedef itk::SmoothingRecursiveGaussianImageFilter<
    ImageType, ImageType >  FilterType;

  FilterType::Pointer smoothingFilter = FilterType::New();
  smoothingFilter->SetInput(this->Image);
  smoothingFilter->SetSigma(value);
  smoothingFilter->Update();

  QPixmap pixmap;
  pixmap.convertFromImage(ITKQtHelpers::GetQImageColor(smoothingFilter->GetOutput()));
  QGraphicsPixmapItem* pixmapItem = this->BlurredScene->addPixmap(pixmap);

  this->gfxviewBlurred->fitInView(pixmapItem);
}
