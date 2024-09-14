#include "src/App.h"
#include "src/header.h"
#include "fstream"

int32_t main(int32_t argc, char *argv[])
{
    QApplication a(argc, argv);
    App TreeManager(800, 800);
    TreeManager.render();
    return QApplication::exec();
}