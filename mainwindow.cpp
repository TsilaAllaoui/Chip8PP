#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "utilities.h"

#include <QFileDialog>
#include <QPainter>
#include <QGraphicsScene>

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

	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGTH; j++)
			img.setPixelColor(i, j, QColor(0,0,0));

	view = ui->view;
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
	/*// Showing states of the CPU
	PC->setText(getAsQStringHex(chip8Cpu->getPC()));
	SP->setText(getAsQStringHex(chip8Cpu->getSP()));
	I->setText(getAsQStringHex(chip8Cpu->getI()));
	DT->setText(getAsQStringHex(chip8Cpu->getDT()));
	ST->setText(getAsQStringHex(chip8Cpu->getST()));

	auto r = chip8Cpu->getRegisters();
	for (int i = 0; i < 16; i++)
		Registers[i]->setText(getAsQStringHex(r[i]));

	// Set current opcode as the current opcode pointed by PC
	if (state != STATE::STOPPED)
	{
		auto mnemonics = chip8Cpu->getMnemonics();
		for (int i = 0; i < mnemonics.size(); i++)
		{
			if (mnemonics[i].find(getAsQStringHex(chip8Cpu->getPC()).toStdString()) != mnemonics[i].npos)
			{
				opcodes->setCurrentRow(i);
				opcodes->currentItem()->setBackgroundColor(QColor(0, 0, 255));
				break;
			}
		}

		// for the color of the current index
		auto it = std::find(breakpoints.begin(), breakpoints.end(), chip8Cpu->getPC());
		if (it != breakpoints.end())
			opcodes->currentItem()->setBackgroundColor(QColor(255, 0, 0));
		else opcodes->currentItem()->setBackgroundColor(QApplication::palette().color(QPalette::Base));
	}
	else opcodes->setCurrentRow(-1);*/

	
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

		updateUI();
	}

	//If the CPU is running, fo a CPU step
	if (Cpu::state == Cpu::STATE::RUNNING)
	{
		chip8Cpu->step();
	}

	// Update the UI
	updateUI();
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
	QString file = QFileDialog::getOpenFileName(nullptr, QString(""), QString("./"), QString("Chip8 ROM (*.ch8 * .c8)"));

	// Loading Rom file
	if (file != QString(""))
	{
		// Resetting the CPU
		chip8Cpu->reset();

		// Loading file into memory
		chip8Cpu->loadRom(file.toStdString());

		// Loading disassembler opcodes
		auto mnemonics = chip8Cpu->getMnemonics();
		for (long i = 0; i < mnemonics.size(); i++)
			opcodes->addItem(QString(mnemonics[i].c_str()));

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
