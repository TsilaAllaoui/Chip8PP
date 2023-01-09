#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include "cpu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();

		// Labels
		QLabel* PC;
		QLabel* SP;
		QLabel* I;
		QLabel* DT;
		QLabel* ST;
		std::vector<QLabel*> Registers;

		// Disassembler
		QListWidget* opcodes;

		// State buttons
		QPushButton* resumePauseButton;
		QPushButton* resetButton;

		// Step button
		QPushButton* stepButton;

		// Updating UI
		void updateUI();

		// Updating window
		void update();

		// Emulate the chip8
		void emulate();

	public slots:

		// For resuming/pausing CPU
		void on_resumePauseButton_clicked();

		// For resetting CPU
		void on_resetButton_clicked();

		// For stepping the CPU
		void on_stepButton_clicked();

	private:
		Ui::MainWindow *ui;

		// The Chip8 CPU
		Cpu* chip8Cpu;
	
		// The current state of the Chip8 eumlator
		bool running;
};
#endif // MAINWINDOW_H
