#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#if _NT
#include <QtPlugin>
Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin)
#endif

void setupHelloQt() {
    // Create the main application window
    QWidget window;
    window.setWindowTitle("Hello, Qt!");

    // Create a label and set its text
    QLabel *label = new QLabel("Hello, Qt!");

    // Create a layout and set it for the main window
    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->addWidget(label);

    // Show the main window
    window.show();
}
