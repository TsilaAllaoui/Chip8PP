#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include "cpu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

	public:

		enum STATE {STOPPED, RUNNING};

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

		// Menu
		QAction* openFileAction;

		// Updating UI
		void updateUI();

		// Updating window
		void update();

		// Emulate the chip8
		void emulate();

		// State of the emulator
		STATE state;

	public slots:

		// For resuming/pausing CPU
		void on_resumePauseButton_clicked();

		// For resetting CPU
		void on_resetButton_clicked();

		// For stepping the CPU
		void on_stepButton_clicked();

		// Choose and load a rom File
		void on_actionOpen_ROM_triggered();

		void on_disassemblerList_currentRowChanged(int currentRow)
		{
			// Get the current and previous items
			QListWidgetItem *currentItem = opcodes->item(currentRow);
			QListWidgetItem *previousItem = opcodes->item(currentRow - 1);

			// Animate the transition between the two items
			if (currentItem && previousItem) {
				QPropertyAnimation *animation = new QPropertyAnimation((QObject*)currentItem, QByteArray("background-color"));
				animation->setDuration(200);
				animation->setStartValue(QColor(Qt::white));
				animation->setEndValue(QColor(Qt::blue));
				animation->start(QAbstractAnimation::DeleteWhenStopped);
			}
		}


	private:
		Ui::MainWindow *ui;

		// The Chip8 CPU
		Cpu* chip8Cpu;
	
		// The current state of the Chip8 eumlator
		bool running;
};
#endif // MAINWINDOW_H
