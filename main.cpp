#include "OOP_Assignment11.h"
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QtWidgets/QMainWindow>
#include "TurretsGUI.h"
#include <vector>
#include "RepositoryBase.h"
#include "Repo.h"
#include "RepositoryText.h"
#include "RepositoryCSV.h"
#include "Service.h"
#include "ServiceWatchMan.h"
#include <QDebug>
#include <QMessageBox>
#include <exception>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	std::vector<Turret> turrets;
	
	ifstream config;
	config.open("config.cfg");
	string whatRepository;
	getline(config, whatRepository);

	RepositoryBase* repo;

	if (whatRepository == "memory")
	{
		repo=new Repository;
	}
	else if(whatRepository == "file")
	{
		repo=new RepositoryText;
	}
	else
	{
		throw exception("Bad config file\n");
	}
	
	Service service(repo);
	ServiceWatchMan serviceWatch(repo);
	OOP_Assignment11 GUI{ service, serviceWatch};
	GUI.show();
	
	app.exec();
	}
