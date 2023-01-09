#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	// Main Qt App
    QApplication a(argc, argv);

	// The UI of the emulator
    MainWindow chip8Emulator;
	chip8Emulator.show();

	// start emulation
	chip8Emulator.emulate();

	// At App loop
    a.exec();

	return 0;
}
