#include "TurretsGUI.h"
#include <QMessageBox>
#include <string>
#include <QDebug>
#include <qcombobox.h>

TurretsGUI::TurretsGUI(std::vector<Turret> _turrets, Service* service, ServiceWatchMan* serviceWatch, QWidget* parent): QWidget{ parent }
{
	this->service = service;
	this->serviceWatch = serviceWatch;
	this->initGUI();
	this->connectSignalsAndSlots();
}

TurretsGUI::~TurretsGUI()
{
	this->service = NULL;
	this->serviceWatch = NULL;
}

void TurretsGUI::initGUI()
{
	QMessageBox* box= new QMessageBox;
	box->setWindowTitle("Something went wrong");
	box->setText("!!!Please select a mode!!!");
	QFont boxFont("Arial", 25);
	box->setFont(boxFont);
	box->setStandardButtons(QMessageBox::Ok);
	box->show();

	QWidget* mainWidget = new QWidget();
	QHBoxLayout* mainLayout = new QHBoxLayout(mainWidget);

	QWidget* leftSide = new QWidget();
	QVBoxLayout* leftLayout = new QVBoxLayout(leftSide);

	QLabel* turretsLabel = new QLabel("All turrets");
	leftLayout->addWidget(turretsLabel);

	this->turretsList = new QListWidget{};
	this->turretsList->setSelectionMode(QAbstractItemView::SingleSelection);
	leftLayout->addWidget(this->turretsList);

	QWidget* turretDataWidget = new QWidget();
	QFormLayout* dataLayout = new QFormLayout(turretDataWidget);
	this->locationLine = new QLineEdit();
	this->sizeLine = new QLineEdit();
	this->auraLine = new QLineEdit();
	this->partsLine = new QLineEdit();
	this->visionLine = new QLineEdit();
	QFont font("Arial", 15);
	QLabel* locationLabel = new QLabel("Location: ");
	QLabel* sizeLabel = new QLabel("Size: ");
	QLabel* auraLabel = new QLabel("Aura: ");
	QLabel* partsLabel = new QLabel("Separate Parts: ");
	QLabel* visionLabel = new QLabel("Vision: ");
	locationLabel->setBuddy(this->locationLine);
	sizeLabel->setBuddy(this->sizeLine);
	auraLabel->setBuddy(this->auraLine);
	partsLabel->setBuddy(this->partsLine);
	visionLabel->setBuddy(this->visionLine);
	locationLabel->setFont(font);
	sizeLabel->setFont(font);
	auraLabel->setFont(font);
	partsLabel->setFont(font);
	visionLabel->setFont(font);
	this->locationLine->setFont(font);
	this->sizeLine->setFont(font);
	this->auraLine->setFont(font);
	this->partsLine->setFont(font);
	this->visionLine->setFont(font);
	dataLayout->addRow(locationLabel, this->locationLine);
	dataLayout->addRow(sizeLabel, this->sizeLine);
	dataLayout->addRow(auraLabel, this->auraLine);
	dataLayout->addRow(partsLabel, this->partsLine);
	dataLayout->addRow(visionLabel, this->visionLine);
	leftLayout->addWidget(turretDataWidget);

	QWidget* buttonsLeftWidget = new QWidget();
	QHBoxLayout* buttonLeftLayout = new QHBoxLayout(buttonsLeftWidget);
	this->addTurretButton = new QPushButton("Add Turret");
	this->deleteTurretButton = new QPushButton("Delete Turret");
	this->updateTurretButton = new QPushButton("Update Turret");
	this->saveTurretButton = new QPushButton("Save turret");
	this->addTurretButton->setFont(font);
	this->deleteTurretButton->setFont(font);
	this->updateTurretButton->setFont(font);
	this->saveTurretButton->setFont(font);
	buttonLeftLayout->addWidget(this->addTurretButton);
	buttonLeftLayout->addWidget(this->deleteTurretButton);
	buttonLeftLayout->addWidget(this->updateTurretButton);
	buttonLeftLayout->addWidget(this->saveTurretButton);
	leftLayout->addWidget(buttonsLeftWidget);

	QWidget* changeMainPathWidget = new QWidget();
	QHBoxLayout* mainPathLayout = new QHBoxLayout(changeMainPathWidget);

	QWidget* mainPathWidget = new QWidget();
	QFormLayout* mainPathFormLayout = new QFormLayout(mainPathWidget);
	this->mainListPath = new QLineEdit;
	this->mainListPath->setFont(font);
	QLabel* mainListLabel = new QLabel("Main List Path: ");
	mainListLabel->setFont(font);
	mainListLabel->setBuddy(this->mainListPath);
	mainPathFormLayout->addRow(mainListLabel, this->mainListPath);
	mainPathLayout->addWidget(mainPathWidget);

	this->changeMainPathButton = new QPushButton("Change Path");
	this->changeMainPathButton->setFont(font);
	mainPathLayout->addWidget(this->changeMainPathButton);


	mainLayout->addWidget(leftSide);

	QWidget* rightSideWidget = new QWidget();
	QVBoxLayout* rightLayout = new QVBoxLayout(rightSideWidget);

	this->modeChangeBox = new QComboBox(rightSideWidget);
	this->modeChangeBox->addItem("Please select a mode");
	this->modeChangeBox->addItem("Mode A");
	this->modeChangeBox->addItem("Mode B");

	rightLayout->addWidget(this->modeChangeBox);

	QLabel* turretsActivatedLabel = new QLabel("All activated turrets");
	rightLayout->addWidget(turretsActivatedLabel);

	this->turretsActivatedList = new QListWidget();
	this->turretsActivatedList->setSelectionMode(QAbstractItemView::SingleSelection);
	rightLayout->addWidget(this->turretsActivatedList);

	this->nextTurretButton = new QPushButton("Next");
	this->nextTurretButton->setFont(font);
	rightLayout->addWidget(this->nextTurretButton);

	QWidget* myListWidget = new QWidget();
	QHBoxLayout* myListLayout = new QHBoxLayout(myListWidget);

	QWidget* listWidget = new QWidget();
	QFormLayout* listLayout = new QFormLayout(listWidget);
	this->myListPath = new QLineEdit();
	this->myListPath->setFont(font);
	QLabel* listLabel = new QLabel("MyList Path: ");
	listLabel->setFont(font);
	listLabel->setBuddy(this->myListPath);
	listLayout->addRow(listLabel, this->myListPath);
	myListLayout->addWidget(listWidget);

	this->changeMyListPathButton=new QPushButton("Change Path");
	this->changeMyListPathButton->setFont(font);
	myListLayout->addWidget(this->changeMyListPathButton);

	QLabel* criteriaTurrets = new QLabel("Criteria Turrets");
	criteriaTurrets->setFont(font);
	rightLayout->addWidget(criteriaTurrets);

	this->allCriteria = new QListWidget();
	this->allCriteria->setSelectionMode(QAbstractItemView::SingleSelection);
	rightLayout->addWidget(this->allCriteria);

	this->allCriteriaButton = new QPushButton("Get all turrets by criteria");
	this->allCriteriaButton->setFont(font);
	rightLayout->addWidget(this->allCriteriaButton);

	this->openButton = new QPushButton("Open");
	this->openButton->setFont(font);
	rightLayout->addWidget(this->openButton);

	mainLayout->addWidget(rightSideWidget);

	QVBoxLayout* masterLayout = new QVBoxLayout(this);

	masterLayout->addWidget(mainWidget);
	masterLayout->addWidget(changeMainPathWidget);
	masterLayout->addWidget(myListWidget);
}

void TurretsGUI::connectSignalsAndSlots()
{
	QObject::connect(this->addTurretButton, &QPushButton::clicked, this, &TurretsGUI::addTurretButtonHandler);
	QObject::connect(this, &TurretsGUI::addTurretSignal, this, &TurretsGUI::addTurret);
	QObject::connect(this->modeChangeBox, SIGNAL(activated(const QString &)), this, SLOT(modeChange(const QString &)));
	QObject::connect(this, &TurretsGUI::updateTurretListSignal, this, &TurretsGUI::updateTurretList);
	QObject::connect(this, &TurretsGUI::updateMyListSignal, this, &TurretsGUI::updateMyList);
	QObject::connect(this->deleteTurretButton, &QPushButton::clicked, this, &TurretsGUI::deleteTurretButtonHandler);
	QObject::connect(this, &TurretsGUI::deleteTurretSignal, this, &TurretsGUI::deleteTurret);
	QObject::connect(this->updateTurretButton, &QPushButton::clicked, this, &TurretsGUI::updateTurretButtonHandler);
	QObject::connect(this, &TurretsGUI::updateTurretSignal, this, &TurretsGUI::updateTurret);
	QObject::connect(this->saveTurretButton, &QPushButton::clicked, this, &TurretsGUI::saveTurretButtonHandler);
	QObject::connect(this, &TurretsGUI::saveTurretSignal, this, &TurretsGUI::saveTurret);
	QObject::connect(this->changeMainPathButton, &QPushButton::clicked, this, &TurretsGUI::changeMainPathButtonHandler);
	QObject::connect(this, &TurretsGUI::changeMainPathSignal, this, &TurretsGUI::changeMainPath);
	QObject::connect(this->changeMyListPathButton, &QPushButton::clicked, this, &TurretsGUI::changeMyListPathButtonHandler);
	QObject::connect(this, &TurretsGUI::changeMyListPathSignal, this, &TurretsGUI::changeMyListPath);
	QObject::connect(this->nextTurretButton, &QPushButton::clicked, this, &TurretsGUI::nextButtonHandler);
	QObject::connect(this->allCriteriaButton, &QPushButton::clicked, this, &TurretsGUI::allCriteriaButtonHandler);
	QObject::connect(this, &TurretsGUI::allCriteriaSignal, this, &TurretsGUI::allCriteriaPopulate);
	QObject::connect(this->openButton, &QPushButton::clicked, this, &TurretsGUI::openButtonHandler);
}

void TurretsGUI::updateTurretList()
{
	try 
	{
		if (this->turretsList->count() > 0)
			this->turretsList->clear();

		for (auto turret : this->service->get_all_service())
		{
			QString turretInList = QString::fromStdString(turret.get_location() + " " + turret.get_size() + " " + to_string(turret.get_auraLevel()) + " " + to_string(turret.get_separateParts()) + " " + turret.get_vision());
			QFont font("Arial", 15);
			QListWidgetItem* turretItem = new QListWidgetItem(turretInList);
			turretItem->setFont(font);
			this->turretsList->addItem(turretItem);
		}
		if (this->turretsList->count() > 0)
			this->turretsList->setCurrentRow(0);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void TurretsGUI::updateMyList()
{
	try
	{
		if (this->turretsActivatedList->count() > 0)
			this->turretsActivatedList->clear();

		std::vector<Turret> turrets = this->serviceWatch->get_all_activated_turrets();

		for (auto turret : turrets)
		{
			QString turretInList = QString::fromStdString(turret.get_location() + " " + turret.get_size() + " " + to_string(turret.get_auraLevel()) + " " + to_string(turret.get_separateParts()) + " " + turret.get_vision());
			QFont font("Arial", 15);
			QListWidgetItem* turretItem = new QListWidgetItem(turretInList);
			turretItem->setFont(font);
			this->turretsActivatedList->addItem(turretItem);
		}
		if (this->turretsActivatedList->count() > 0)
			this->turretsActivatedList->setCurrentRow(0);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::addTurretButtonHandler()
{
	try
	{
		QString errors;
		std::string location = (this->locationLine->text()).toStdString();
		if (location == "")
		{
			errors += "invalid location\n";
		}

		std::string size = (this->sizeLine->text()).toStdString();
		if (size == "")
		{
			errors += "invalid size\n";
		}

		int aura = (this->auraLine->text()).toInt();
		if (aura == 0)
		{
			errors += "Invalid aura level\n";
		}

		int parts = (this->partsLine->text()).toInt();
		if (parts == 0)
		{
			errors += "Invalid seprate parts\n";
		}

		std::string vision = (this->visionLine->text()).toStdString();
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
			emit addTurretSignal(location, size, aura, parts, vision);
		}
		this->emptyLines();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
	
}

void TurretsGUI::deleteTurretButtonHandler()
{
	try
	{
		string location = ((this->locationLine)->text()).toStdString();
		if (location == "")
		{
			this->showMessageBox("Invalid location");
		}
		else
		{
			emit deleteTurretSignal(location);
		}
		this->emptyLines();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::updateTurretButtonHandler()
{
	try
	{
		QString errors;
		std::string location = (this->locationLine->text()).toStdString();
		if (location == "")
		{
			errors += "invalid location\n";
		}

		std::string size = (this->sizeLine->text()).toStdString();
		if (size == "")
		{
			errors += "invalid size\n";
		}

		int aura = (this->auraLine->text()).toInt();
		if (aura == 0)
		{
			errors += "Invalid aura level\n";
		}

		int parts = (this->partsLine->text()).toInt();
		if (parts == 0)
		{
			errors += "Invalid seprate parts\n";
		}

		std::string vision = (this->visionLine->text()).toStdString();
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
			emit updateTurretSignal(location, size, aura, parts, vision);
		}
		this->emptyLines();

	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::saveTurretButtonHandler()
{
	try
	{
		string location = ((this->locationLine)->text()).toStdString();
		if (location == "")
		{
			this->showMessageBox("Invalid location");
		}
		else
		{
			emit saveTurretSignal(location);
		}
		this->emptyLines();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::changeMainPathButtonHandler()
{
	try
	{
		string path = this->mainListPath->text().toStdString();
		emit changeMainPathSignal(path);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::changeMyListPathButtonHandler()
{
	try
	{
		string path = this->myListPath->text().toStdString();
		emit changeMyListPathSignal(path);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::nextButtonHandler()
{
	try
	{
		this->turretsList->setCurrentRow(this->serviceWatch->next());
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
}

void TurretsGUI::allCriteriaButtonHandler()
{
	try
	{
		string size = this->sizeLine->text().toStdString();
		int parts = this->partsLine->text().toInt();
		std::vector<Turret> turrets = this->serviceWatch->get_all_criteria(size, parts);
		this->emptyLines();
		emit allCriteriaSignal(turrets);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::openButtonHandler()
{
	try 
	{
		this->serviceWatch->open();
	}
	catch (...)
	{

	}
}

void TurretsGUI::showMessageBox(QString message)
{
	QMessageBox box;
	box.setWindowTitle("Something went wrong");
	box.setText(message);
	box.setStandardButtons(QMessageBox::Ok);
	box.exec();
}

void TurretsGUI::emptyLines()
{
	this->locationLine->setText("");
	this->sizeLine->setText("");
	this->auraLine->setText("");
	this->partsLine->setText("");
	this->visionLine->setText("");
}

void TurretsGUI::addTurret(std::string location, std::string size, int auraLevel, int separateParts, std::string vision)
{
	try
	{
		this->service->add_from_service(location, size, auraLevel, separateParts, vision);
		emit updateTurretListSignal();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::updateTurret(std::string location, std::string size, int auraLevel, int separateParts, std::string vision)
{
	try
	{
		this->service->update_from_service(location, size, auraLevel, separateParts, vision);
		emit updateTurretList();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::saveTurret(std::string location)
{
	try
	{
		this->serviceWatch->save(location);
		emit updateMyListSignal();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::modeChange(const QString &mode)
{
	try
	{
		string Mode = mode.toStdString();
		Mode.erase(0, 5);
		this->service->change_mode(Mode);
		this->serviceWatch->change_mode(Mode);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::changeMainPath(string location)
{
	try
	{
		this->service->change_fileLocation(location);
		emit updateTurretListSignal();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::changeMyListPath(string path)
{
	try
	{
		this->serviceWatch->save_to_format(path);
		emit updateMyListSignal();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::allCriteriaPopulate(std::vector<Turret> turrets)
{
	try
	{
		if (this->allCriteria->count() > 0)
			this->allCriteria->clear();

		for (auto& turret : turrets)
		{
			QString turretInList = QString::fromStdString(turret.get_location() + " " + turret.get_size() + " " + to_string(turret.get_auraLevel()) + " " + to_string(turret.get_separateParts()) + " " + turret.get_vision());
			QFont font("Arial", 15);
			QListWidgetItem* turretItem = new QListWidgetItem(turretInList);
			turretItem->setFont(font);
			this->allCriteria->addItem(turretItem);
		}

		if (this->allCriteria->count() > 0)
			this->allCriteria->setCurrentRow(0);
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

void TurretsGUI::deleteTurret(string path)
{
	try
	{
		this->service->delete_from_service(path);
			emit updateTurretListSignal();
	}
	catch (exception& Exception)
	{
		this->showMessageBox(Exception.what());
	}
	
}

