#include "OOP_Assignment11.h"
#include <QtWidgets/QMainWindow>
#include "Turret.h"
#include <QMessageBox>
#include <string>
#include <QDebug>
#include <qcombobox.h>
#include <QShortcut>
#include "SecondaryWindow.h"


OOP_Assignment11::OOP_Assignment11(Service& serv, ServiceWatchMan& servWatch, QWidget *parent) : service{ serv }, serviceWatch{ servWatch }, QMainWindow(parent)
{
	ui.setupUi(this);
	QShortcut* undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
	QObject::connect(undoShortcut, &QShortcut::activated, this, &OOP_Assignment11::undo);

	QShortcut* redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &OOP_Assignment11::redo);
}

void OOP_Assignment11::addTurret()
{
	try
	{
		QString errors;
		std::string location = (this->ui.locationLine->text()).toStdString();
		if (location == "")
		{
			errors += "invalid location\n";
		}

		std::string size = (this->ui.sizeLine->text()).toStdString();
		if (size == "")
		{
			errors += "invalid size\n";
		}

		int aura = (this->ui.auraLine->text()).toInt();
		if (aura == 0)
		{
			errors += "Invalid aura level\n";
		}

		int parts = (this->ui.partsLine->text()).toInt();
		if (parts == 0)
		{
			errors += "Invalid seprate parts\n";
		}

		std::string vision = (this->ui.visionLine->text()).toStdString();
		if (vision == "")
		{
			errors += "invalid vision\n";
		}

		if (!errors.isEmpty())
		{
			this->showMessageBox(errors);
		}
		else
		{
			this->service.add_from_service(location, size, aura, parts, vision);
			this->updateMainList();
		}
		this->emptyLines();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void OOP_Assignment11::showMessageBox(QString message)
{
	QMessageBox box;
	box.setWindowTitle("Something went wrong");
	box.setText(message);
	box.setStandardButtons(QMessageBox::Ok);
	box.exec();
}

void OOP_Assignment11::emptyLines()
{
	this->ui.locationLine->setText("");
	this->ui.sizeLine->setText("");
	this->ui.auraLine->setText("");
	this->ui.partsLine->setText("");
	this->ui.visionLine->setText("");
}

void OOP_Assignment11::updateMainList()
{
	try
	{
		if (this->ui.turretsList->count() > 0)
			this->ui.turretsList->clear();
		for (auto& turret : this->service.get_all_service())
		{
			QString turretInList = QString::fromStdString(turret.get_location() + " " + turret.get_size() + " " + to_string(turret.get_auraLevel()) + " " + to_string(turret.get_separateParts()) + " " + turret.get_vision());
			QFont font("Arial", 15);
			QListWidgetItem* turretItem = new QListWidgetItem(turretInList);
			turretItem->setFont(font);
			this->ui.turretsList->addItem(turretItem);
		}
		if (this->ui.turretsList->count() > 0)
			this->ui.turretsList->setCurrentRow(0);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void OOP_Assignment11::updateMyList(vector<Turret> turrets)
{
	try
	{
		if (this->ui.allCriteria->count() > 0)
			this->ui.allCriteria->clear();
		for (auto& turret : turrets)
		{
			QString turretInList = QString::fromStdString(turret.get_location() + " " + turret.get_size() + " " + to_string(turret.get_auraLevel()) + " " + to_string(turret.get_separateParts()) + " " + turret.get_vision());
			QFont font("Arial", 15);
			QListWidgetItem* turretItem = new QListWidgetItem(turretInList);
			turretItem->setFont(font);
			this->ui.allCriteria->addItem(turretItem);
		}
		if (this->ui.allCriteria->count() > 0)
			this->ui.allCriteria->setCurrentRow(0);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}


void OOP_Assignment11::removeTurret()
{
	try
	{
		string location = ((this->ui.locationLine)->text()).toStdString();
		if (location == "")
		{
			this->showMessageBox("Invalid location");
		}
		else
		{
			this->emptyLines();
			this->service.delete_from_service(location);
			this->serviceWatch.delete_from_service_watchman(location);
			this->updateMainList();
		}
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void OOP_Assignment11::updateTurret()
{
	try
	{
		QString errors;
		std::string location = (this->ui.locationLine->text()).toStdString();
		if (location == "")
		{
			errors += "invalid location\n";
		}

		std::string size = (this->ui.sizeLine->text()).toStdString();
		if (size == "")
		{
			errors += "invalid size\n";
		}

		int aura = (this->ui.auraLine->text()).toInt();
		if (aura == 0)
		{
			errors += "Invalid aura level\n";
		}

		int parts = (this->ui.partsLine->text()).toInt();
		if (parts == 0)
		{
			errors += "Invalid seprate parts\n";
		}

		std::string vision = (this->ui.visionLine->text()).toStdString();
		if (vision == "")
		{
			errors += "invalid vision\n";
		}

		if (!errors.isEmpty())
		{
			this->showMessageBox(errors);
		}
		else
		{
			this->emptyLines();
			this->service.update_from_service(location, size, aura, parts, vision);
			this->serviceWatch.update_from_service_watchman(location, size, aura, parts, vision);
			this->updateMainList();
		}
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void OOP_Assignment11::saveTurret()
{
	try
	{
		string location = ((this->ui.locationLine)->text()).toStdString();
		if (location == "")
		{
			this->showMessageBox("Invalid location");
		}
		else
		{
			this->serviceWatch.save(location);
			
		}
		this->emptyLines();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void OOP_Assignment11::changeMainPath()
{
	try
	{
		string path = this->ui.mainListPath->text().toStdString();
		this->service.change_fileLocation(path);
		this->updateMainList();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void OOP_Assignment11::changeMyListPath()
{
	try
	{
		string path = this->ui.myListPath->text().toStdString();
		this->serviceWatch.save_to_format(path);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void OOP_Assignment11::nextTurret()
{
	try
	{
		this->ui.turretsList->setCurrentRow(this->serviceWatch.next());
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void OOP_Assignment11::changeMode(const QString& mode)
{
	try
	{
		string Mode = mode.toStdString();
		Mode.erase(0, 5);
		this->service.change_mode(Mode);
		this->serviceWatch.change_mode(Mode);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void OOP_Assignment11::undo()
{
	try 
	{
		this->service.undo();
		this->updateMainList();
	}
	catch (exception& error)
	{
		this->showMessageBox(error.what());
	}
}

void OOP_Assignment11::redo()
{
	try
	{
		this->service.redo();
		this->updateMainList();
	}
	catch (exception& error)
	{
		this->showMessageBox(error.what());
	}
}

void OOP_Assignment11::openWindow()
{
	try
	{
		SecondaryWindow* myListWindow= new SecondaryWindow(this->serviceWatch);
		myListWindow->show();
	}
	catch (exception& error)
	{
		this->showMessageBox(error.what());
	}
}

void OOP_Assignment11::openMyList()
{
	try
	{
		this->serviceWatch.open();
	}
	catch (...)
	{

	}
}

void OOP_Assignment11::filterCriteria()
{
	try
	{
		string size = this->ui.sizeLine->text().toStdString();
		int parts = this->ui.partsLine->text().toInt();
		std::vector<Turret> turrets = this->serviceWatch.get_all_criteria(size, parts);
		this->emptyLines();
		this->updateMyList(turrets);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}
