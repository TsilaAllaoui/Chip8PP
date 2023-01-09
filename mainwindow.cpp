#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "utilities.h"

#include <QFileDialog>

uint16_t prevPC = 0;
long _i = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Set the state of the emulator
	running = false;
	state = STATE::STOPPED;

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
	opcodes->setStyleSheet("QListWidget::item::selected {background: blue; color: white; transition: background 300ms;}");


	// Setting up buttons
	resumePauseButton = ui->resumePauseButton;
	resetButton = ui->resetButton;

	// Actions
	openFileAction = ui->menubar->actions().at(0);

	// First update of the UI
	updateUI();
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
		else if (Cpu::state == Cpu::STATE::PAUSED || Cpu::state == Cpu::STATE::STEP)
		{
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
	// Showing states of the CPU
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
		for (int i=0; i<mnemonics.size(); i++)
		{
			if (mnemonics[i].find(getAsQStringHex(chip8Cpu->getPC()).toStdString()) != mnemonics[i].npos)
			{
				opcodes->setCurrentRow(i);
				break;
			}
		}
	}
	else opcodes->setCurrentRow(-1);

}

void MainWindow::update()
{
	// Prevent the UI to be unresponsive
	QApplication::instance()->processEvents();

	//If the CPU is running, fo a CPU step
	if (Cpu::state == Cpu::STATE::RUNNING)
		chip8Cpu->step();

	// Update the UI
	updateUI();
}

void MainWindow::emulate()
{
	while (state == STATE::RUNNING)
	{
		prevPC = chip8Cpu->getPC();
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
