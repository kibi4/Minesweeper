#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Initialize the Qt application

    MainWindow window;  // Create the main window
    window.show();  // Show the window

    return app.exec();  // Start the event loop
}
