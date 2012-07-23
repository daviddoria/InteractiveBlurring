#include <QApplication>
#include <QCleanlooksStyle>

#include "InteractiveBlurringWidget.h"

int main( int argc, char** argv )
{
  QApplication app( argc, argv );

  QApplication::setStyle(new QCleanlooksStyle);

  InteractiveBlurringWidget interactiveBlurringWidget;
  interactiveBlurringWidget.show();

  return app.exec();
}
