#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "utilities.h"

#include <QGraphicsScene>
#include <QFileDialog>
#include <QKeyEvent>
#include <algorithm>
#include <QPainter>
#include <fstream>
#include <vector>
#include <string>

QImage MainWindow::img;

#define WIDTH 64
#define HEIGTH 32
#define SIZEFACTOR 4

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Set the state of the emulator
	running = false;
	state = STATE::STOPPED;
	isInBreakPoint = false;

	// Instance of the CPU
	chip8Cpu = new Cpu();

	// Setting up attributes widgets
	PC = ui->PC;
	SP = ui->SP;
	I = ui->I;
	DT = ui->DT;
	ST = ui->ST;
	Registers.emplace_back(ui->V0);
	Registers.emplace_back(ui->V1);
	Registers.emplace_back(ui->V2);
	Registers.emplace_back(ui->V3);
	Registers.emplace_back(ui->V4);
	Registers.emplace_back(ui->V5);
	Registers.emplace_back(ui->V6);
	Registers.emplace_back(ui->V7);
	Registers.emplace_back(ui->V8);
	Registers.emplace_back(ui->V9);
	Registers.emplace_back(ui->VA);
	Registers.emplace_back(ui->VB);
	Registers.emplace_back(ui->VC);
	Registers.emplace_back(ui->VD);
	Registers.emplace_back(ui->VE);
	Registers.emplace_back(ui->VF);

	// Setting up disassembler widgets
	opcodes = ui->disassemblerList;
	opcodes->setStyleSheet("QListWidget::item::selected {background: blue; color: white;}");

	// Setting up breakpoints widgets
	breakpointsList = ui->breakpointsList;


	// Setting up buttons
	resumePauseButton = ui->resumePauseButton;
	resetButton = ui->resetButton;

	// Actions
	openFileAction = ui->menubar->actions().at(0);

	// First update of the UI
	updateUI();


	// GRAPHICS

	img = QImage(WIDTH, HEIGTH, QImage::Format::Format_RGB888);
	img.fill(QColor(0, 0, 0));

	view = ui->view;

	// Setting up focus of window for key event
	this->setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_resumePauseButton_clicked()
{
	// If the emulator is running
	if (state == STATE::RUNNING)
	{
		// If the CPU is runnig, then pause it
		if (Cpu::state == Cpu::STATE::RUNNING)
		{
			Cpu::state = Cpu::STATE::PAUSED;
			resumePauseButton->setText(QString("RESUME"));
		}

		// If the CPU is paused, then resume it
		else if (Cpu::state == Cpu::STATE::PAUSED || Cpu::state == Cpu::STATE::STEP )
		{
			if (isInBreakPoint == true)
			{
				isInBreakPoint = false;
				chip8Cpu->step();
			}

			Cpu::state = Cpu::STATE::RUNNING;
			resumePauseButton->setText(QString("PAUSE"));
		}
	}
}

void MainWindow::on_resetButton_clicked()
{
	// If the emulator is running
	if (state == STATE::RUNNING)
	{
		// If the CPU is runnig, then pause it
		if (Cpu::state == Cpu::STATE::RUNNING)
			Cpu::state = Cpu::STATE::PAUSED;

		// Reset the CPU
		chip8Cpu->reset();

		// Clearing screen
		img.fill(QColor(0,0,0));

		// Update the UI
		updateUI();
	}
}

void MainWindow::on_stepButton_clicked()
{
	// If the emulator is running
	if (state == STATE::RUNNING)
	{
		// If the CPU is runnig, then set mode to STEP mode
		Cpu::state = Cpu::STATE::STEP;
		resumePauseButton->setText(QString("RESUME"));

		// Do a CPU step
		chip8Cpu->step();

		// Update UI
		updateUI();
	}
}

void MainWindow::updateUI()
{
	// Showing states of the CPU
	PC->setText(getAsQStringHex(chip8Cpu->getPC()));
	SP->setText(getAsQStringHex(chip8Cpu->getSP()));
	I->setText(getAsQStringHex(chip8Cpu->getI()));
	DT->setText(getAsQStringHex(chip8Cpu->getDT()));
	ST->setText(getAsQStringHex(chip8Cpu->getST()));

	auto r = chip8Cpu->getRegisters();
	for (int i = 0; i < 16; i++)
		Registers[i]->setText(getAsQStringHex(r[i]));

	// Upfating stack
	auto stackList = chip8Cpu->getStack();
	ui->stackList->clear();
	for (auto &i : stackList)
	{
		ui->stackList->addItem(getAsQStringHex(i));
	}

	// Set current opcode as the current opcode pointed by PC
	if (state != STATE::STOPPED)
	{
		auto mnemonics = chip8Cpu->getMnemonics();
		if (!mnemonics[chip8Cpu->getPC()].empty())
		{
			auto t = mnemonicsIndexes[mnemonics[chip8Cpu->getPC()]];
		 	opcodes->setCurrentRow(t);
			opcodes->currentItem()->setBackgroundColor(QColor(0, 0, 255));
		}

		// for the color of the current index
		auto it = std::find(breakpoints.begin(), breakpoints.end(), chip8Cpu->getPC());
		if (it != breakpoints.end())
			opcodes->currentItem()->setBackgroundColor(QColor(255, 0, 0));
		else opcodes->currentItem()->setBackgroundColor(QApplication::palette().color(QPalette::Base));
	}

	else opcodes->setCurrentRow(-1);

}

void MainWindow::update()
{
	// Prevent the UI to be unresponsive
	QApplication::instance()->processEvents();

	// If the current PC is at a breakpoint
	auto it = std::find(breakpoints.begin(), breakpoints.end(), chip8Cpu->getPC());
	if (it != breakpoints.end())
	{
		isInBreakPoint = true;
		Cpu::state = Cpu::STATE::STEP;
		resumePauseButton->setText(QString("RESUME"));

		//opcodes->currentItem()->setBackgroundColor(QApplication::palette().color(QPalette::Base));

		//updateUI();
	}

	//If the CPU is running, fo a CPU step
	if (Cpu::state == Cpu::STATE::RUNNING)
	{
		chip8Cpu->step();
	}

	// Update the UI
	//updateUI();

}

void MainWindow::emulate()
{
	while (state == STATE::RUNNING)
	{
		update();
	}
}

void MainWindow::on_actionOpen_ROM_triggered()
{
	// Getting the Rom file
	QString file = QFileDialog::getOpenFileName(nullptr, QString(""), QString("./Roms/"), QString("Chip8 ROM (*.ch8 * .c8)"));
	//QString file = "C:/Users/735/Desktop/Chip8PP/chip8-test-suite.ch8";
	// Loading Rom file
	if (file != QString(""))
	{
		// Resetting the CPU
		chip8Cpu->reset();

		// Loading file into memory
		chip8Cpu->loadRom(file.toStdString());

		// Loading disassembler opcodes
		mnemonicsIndexes.clear();
		auto mnemonics = chip8Cpu->getMnemonics();
		for (auto& i : mnemonics)
		{
			opcodes->addItem(QString(i.second.c_str()));
			mnemonicsIndexes[i.second] = mnemonicsIndexes.size();
		}

		// Setting states
		Cpu::state = Cpu::STATE::RUNNING;
		state = STATE::RUNNING;

		// Emulate the Chip8
		emulate();
	}
}

void MainWindow::on_disassemblerList_itemDoubleClicked(QListWidgetItem *item)
{
	// The current hex index of the item
	uint16_t hex = QStringtoHex(item->text());

	// Erasing if already in list
	for (long i=0; i<breakpoints.size(); i++)
	{
		if (breakpoints[i] == hex)
		{
			 breakpoints.erase(breakpoints.begin() + i);

			 // Readding all items then sorting
			 breakpointsList->clear();
			 for (auto &j : breakpoints)
				 breakpointsList->addItem(getAsQStringHex(j));
			 breakpointsList->sortItems(Qt::AscendingOrder);

			 item->setBackgroundColor(QApplication::palette().color(QPalette::Base));
			 return;
		}
	}

	// If not in list, add and change color
	item->setBackgroundColor(QColor(255, 0, 0));
	breakpoints.emplace_back(hex);

	// Add to breakpoints and sort
	breakpointsList->addItem(getAsQStringHex(QStringtoHex(item->text())));
	breakpointsList->sortItems(Qt::AscendingOrder);
}

void MainWindow::paintEvent(QPaintEvent * event)
{
	pix = pix.fromImage(img.scaled(WIDTH * SIZEFACTOR,WIDTH * SIZEFACTOR));
	view->setPixmap(pix);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	std::bitset<16> keys;
	if (event->key() == Qt::Key_0) keys[0] = 1; else keys[0] = 0; 
	if (event->key() == Qt::Key_1) keys[1] = 1; else keys[1] = 0;
	if (event->key() == Qt::Key_2) keys[2] = 1; else keys[2] = 0;
	if (event->key() == Qt::Key_3) keys[3] = 1; else keys[3] = 0;
	if (event->key() == Qt::Key_4) keys[4] = 1; else keys[4] = 0;
	if (event->key() == Qt::Key_5) keys[5] = 1; else keys[5] = 0;
	if (event->key() == Qt::Key_6) keys[6] = 1; else keys[6] = 0;
	if (event->key() == Qt::Key_7) keys[7] = 1; else keys[7] = 0;
	if (event->key() == Qt::Key_8) keys[8] = 1; else keys[8] = 0;
	if (event->key() == Qt::Key_9) keys[9] = 1; else keys[9] = 0;
	if (event->key() == Qt::Key_A) keys[0xA] = 1; else keys[0xA] = 0;
	if (event->key() == Qt::Key_B) keys[0xB] = 1; else keys[0xB] = 0;
	if (event->key() == Qt::Key_C) keys[0xC] = 1; else keys[0xC] = 0;
	if (event->key() == Qt::Key_D) keys[0xD] = 1; else keys[0xD] = 0;
	if (event->key() == Qt::Key_E) keys[0xE] = 1; else keys[0xE] = 0;
	if (event->key() == Qt::Key_F) keys[0xF] = 1; else keys[0xF] = 0;

	chip8Cpu->setKeys(keys);
}

void MainWindow::on_Key0_pressed()
{
	chip8Cpu->setKey(0, 1);
}

void MainWindow::on_Key0_released()
{
	chip8Cpu->setKey(0, 0);
}

void MainWindow::on_Key1_pressed()
{
	chip8Cpu->setKey(1, 1);
}

void MainWindow::on_Key1_released()
{
	chip8Cpu->setKey(1, 0);
}

void MainWindow::on_Key2_pressed()
{
	chip8Cpu->setKey(2, 1);
}

void MainWindow::on_Key2_released()
{
	chip8Cpu->setKey(2, 0);
}

void MainWindow::on_Key3_pressed()
{
	chip8Cpu->setKey(3, 1);
}

void MainWindow::on_Key3_released()
{
	chip8Cpu->setKey(3, 0);
}

void MainWindow::on_Key4_pressed()
{
	chip8Cpu->setKey(4, 1);
}

void MainWindow::on_Key4_released()
{
	chip8Cpu->setKey(4, 0);
}

void MainWindow::on_Key5_pressed()
{
	chip8Cpu->setKey(5, 1);
}

void MainWindow::on_Key5_released()
{
	chip8Cpu->setKey(5, 0);
}

void MainWindow::on_Key6_pressed()
{
	chip8Cpu->setKey(6, 1);
}

void MainWindow::on_Key6_released()
{
	chip8Cpu->setKey(6, 0);
}

void MainWindow::on_Key7_pressed()
{
	chip8Cpu->setKey(7, 1);
}

void MainWindow::on_Key7_released()
{
	chip8Cpu->setKey(7, 0);
}

void MainWindow::on_Key8_pressed()
{
	chip8Cpu->setKey(8, 1);
}

void MainWindow::on_Key8_released()
{
	chip8Cpu->setKey(8, 0);
}

void MainWindow::on_Key9_pressed()
{
	chip8Cpu->setKey(9, 1);
}

void MainWindow::on_Key9_released()
{
	chip8Cpu->setKey(9, 0);
}

void MainWindow::on_KeyA_pressed()
{
	chip8Cpu->setKey(0xA, 1);
}

void MainWindow::on_KeyA_released()
{
	chip8Cpu->setKey(0xA, 0);
}

void MainWindow::on_KeyB_pressed()
{
	chip8Cpu->setKey(0xB, 1);
}

void MainWindow::on_KeyB_released()
{
	chip8Cpu->setKey(0xB, 0);
}

void MainWindow::on_KeyC_pressed()
{
	chip8Cpu->setKey(0xC, 1);
}

void MainWindow::on_KeyC_released()
{
	chip8Cpu->setKey(0xC, 0);
}

void MainWindow::on_KeyD_pressed()
{
	chip8Cpu->setKey(0xD, 1);
}

void MainWindow::on_KeyD_released()
{
	chip8Cpu->setKey(0xD, 0);
}

void MainWindow::on_KeyE_pressed()
{
	chip8Cpu->setKey(0xE, 1);
}

void MainWindow::on_KeyE_released()
{
	chip8Cpu->setKey(0xE, 0);
}

void MainWindow::on_KeyF_pressed()
{
	chip8Cpu->setKey(0xF, 1);
}

void MainWindow::on_KeyF_released()
{
	chip8Cpu->setKey(0xF, 0);
}