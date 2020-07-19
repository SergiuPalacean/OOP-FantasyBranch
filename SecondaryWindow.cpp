#include "SecondaryWindow.h"

SecondaryWindow::SecondaryWindow(ServiceWatchMan& service, QWidget* parent): QMainWindow(parent), serviceWatch{service}
{
	this->ui.setupUi(this);
	this->tableModel = new TurretTableView(this->serviceWatch);
	this->ui.myList->setModel(this->tableModel);
	this->serviceWatch.addObserver(this);
}

void SecondaryWindow::update()
{
	/*delete this->tableModel;
	this->tableModel = new TurretTableView(this->serviceWatch);
	this->ui.myList->setModel(this->tableModel);*/
	emit this->tableModel->dataChanged(QModelIndex(), QModelIndex());
}

void SecondaryWindow::showMessageBox(QString message)
{
	QMessageBox box;
	box.setWindowTitle("Something went wrong");
	box.setText(message);
	box.setStandardButtons(QMessageBox::Ok);
	box.exec();
}

void SecondaryWindow::undo()
{
	try
	{
		this->serviceWatch.undo();
	}
	catch (exception& error)
	{
		this->showMessageBox(error.what());
	}
}

void SecondaryWindow::redo()
{
	try
	{
		this->serviceWatch.redo();
	}
	catch (exception& error)
	{
		this->showMessageBox(error.what());
	}
}
