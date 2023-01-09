#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Set the state of the emulator
	running = true;

	// Instance of the CPU
	chip8Cpu = new Cpu();
	chip8Cpu->loadRom("maze.ch8");

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
	for (long i = 0; i < Cpu::romFileSize; i++)
		opcodes->addItem(QString("0x") + QString("%1").arg(0x200 + i, 0, 16).toUpper());

	// Setting up buttons
	resumePauseButton = ui->resumePauseButton;
	resetButton = ui->resetButton;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_resumePauseButton_clicked()
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

void MainWindow::on_resetButton_clicked()
{
	// If the CPU is runnig, then pause it
	if (Cpu::state == Cpu::STATE::RUNNING)
		Cpu::state = Cpu::STATE::PAUSED;

	// Reset the CPU
	chip8Cpu->reset();

	// Update the UI
	updateUI();
}

void MainWindow::on_stepButton_clicked()
{
	// If the CPU is runnig, then set mode to STEP mode
	Cpu::state = Cpu::STATE::STEP;
	resumePauseButton->setText(QString("RESUME"));

	// Do a CPU step
	chip8Cpu->step();

	// Update UI
	updateUI();
}

void MainWindow::updateUI()
{
	// Showing states of the CPU
	PC->setText(QString("0x") + QString("%1").arg(chip8Cpu->getPC(), 0, 16).toUpper());
	SP->setText(QString("0x") + QString("%1").arg(chip8Cpu->getSP(), 0, 16).toUpper());
	I->setText(QString("0x") + QString("%1").arg(chip8Cpu->getI(), 0, 16).toUpper());
	DT->setText(QString("0x") + QString("%1").arg(chip8Cpu->getDT(), 0, 16).toUpper());
	ST->setText(QString("0x") + QString("%1").arg(chip8Cpu->getST(), 0, 16).toUpper());

	auto r = chip8Cpu->getRegisters();
	for (int i = 0; i < 16; i++)
		Registers[i]->setText(QString("0x") + QString("%1").arg(r[i], 0, 16).toUpper());

	// Set current opcode as the current opcode pointed by PC
	opcodes->setCurrentRow(chip8Cpu->getPC() - 0x200);
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
	while (running)
	{
		update();
	}
}