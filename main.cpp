#include <QApplication>
#include "mainwidget.h"

int main(int c, char **v)
{
   QApplication app(c, v);

   QApplication::setOrganizationName ("Home");
   QApplication::setApplicationName ("FileReaderApplication");


   MainWidget mWidget(NULL);

   mWidget.show();

   return app.exec ();
}

