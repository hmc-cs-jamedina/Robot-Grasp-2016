#include "qtglshader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtGLShader w;
    w.show();

    return a.exec();
}
