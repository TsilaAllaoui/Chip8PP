#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include "cpu.h"
#include <QKeyEvent>

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
		QListWidget* breakpointsList;

		// State buttons
		QPushButton* resumePauseButton;
		QPushButton* resetButton;

		// Step button
		QPushButton* stepButton;

		// Menu
		QAction* openFileAction;

		// For drawing
		static QImage img;
		QPixmap pix;
		QLabel* view;


		// Updating UI
		void updateUI();

		// Updating window
		void update();

		// Emulate the chip8
		void emulate();

		// State of the emulator
		STATE state;

		// Breakpoints
		std::vector<uint16_t> breakpoints;

		// Is the CPU is in a breakpoint
		bool isInBreakPoint;

	public slots:

		// For resuming/pausing CPU
		void on_resumePauseButton_clicked();

		// For resetting CPU
		void on_resetButton_clicked();

		// For stepping the CPU
		void on_stepButton_clicked();

		// Choose and load a rom File
		void on_actionOpen_ROM_triggered();

		// Add breakpoint
		void on_disassemblerList_itemDoubleClicked(QListWidgetItem *item);

		// For rendering
		void paintEvent(QPaintEvent *event) override;
		
		// For key presses
		void keyPressEvent(QKeyEvent *event) override;

		// For all keys pushButton event
		void on_Key0_pressed();
		void on_Key1_pressed();
		void on_Key2_pressed();
		void on_Key3_pressed();
		void on_Key4_pressed();
		void on_Key5_pressed();
		void on_Key6_pressed();
		void on_Key7_pressed();
		void on_Key8_pressed();
		void on_Key9_pressed();
		void on_KeyA_pressed();
		void on_KeyB_pressed();
		void on_KeyC_pressed();
		void on_KeyD_pressed();
		void on_KeyE_pressed();
		void on_KeyF_pressed();

		void on_Key0_released();
		void on_Key1_released();
		void on_Key2_released();
		void on_Key3_released();
		void on_Key4_released();
		void on_Key5_released();
		void on_Key6_released();
		void on_Key7_released();
		void on_Key8_released();
		void on_Key9_released();
		void on_KeyA_released();
		void on_KeyB_released();
		void on_KeyC_released();
		void on_KeyD_released();
		void on_KeyE_released();
		void on_KeyF_released();



	private:
		Ui::MainWindow *ui;

		// The Chip8 CPU
		Cpu* chip8Cpu;
	
		// The current state of the Chip8 eumlator
		bool running;

		//Mnemonics vector
		std::unordered_map<std::string, int> mnemonicsIndexes;
};
#endif // MAINWINDOW_H
