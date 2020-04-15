#include "GuiMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GuiMainWindow window;

    window.setMinimumSize(640,480);
    window.show();

    return app.exec();
}
