#pragma once
#include <qwidget.h>
#include <vector>
#include "Turret.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include "Service.h"
#include "ServiceWatchMan.h"


class TurretsGUI : public QWidget
{
	Q_OBJECT

public:
	TurretsGUI(std::vector<Turret> turrets, Service* service, ServiceWatchMan* serviceWatch, QWidget* parent = 0);

	~TurretsGUI();

private:
	Service* service;
	ServiceWatchMan* serviceWatch;

	//left part
	QListWidget* turretsList;
	QLineEdit* locationLine;
	QLineEdit* sizeLine;
	QLineEdit* auraLine;
	QLineEdit* partsLine;
	QLineEdit* visionLine;
	QPushButton* addTurretButton;
	QPushButton* deleteTurretButton;
	QPushButton* updateTurretButton;
	QPushButton* saveTurretButton;
	QLineEdit* myListPath;
	QLineEdit* mainListPath;
	QPushButton* changeMainPathButton;
	QPushButton* changeMyListPathButton;

	//rigth part
	QListWidget* turretsActivatedList;
	QPushButton* nextTurretButton;
	QComboBox* modeChangeBox;
	QListWidget* allCriteria;
	QPushButton* allCriteriaButton;
	QPushButton* openButton;

	//methods
	void initGUI();
	void connectSignalsAndSlots();
	void updateTurretList();
	void updateMyList();

	void addTurretButtonHandler();
	void deleteTurretButtonHandler();
	void updateTurretButtonHandler();
	void saveTurretButtonHandler();
	void changeMainPathButtonHandler();
	void changeMyListPathButtonHandler();
	void nextButtonHandler();
	void allCriteriaButtonHandler();
	void openButtonHandler();

	//Helper methods
	void showMessageBox(QString message);
	void emptyLines();

signals:
	void addTurretSignal(std::string location, std::string size, int auraLevel, int separateParts, std::string vision);
	void updateTurretListSignal();
	void updateMyListSignal();
	void deleteTurretSignal(string location);
	void updateTurretSignal(std::string location, std::string size, int auraLevel, int separateParts, std::string vision);
	void saveTurretSignal(string location);
	void changeMainPathSignal(string path);
	void changeMyListPathSignal(string path);
	void allCriteriaSignal(std::vector<Turret> turrets);

private slots:
	void addTurret(std::string location, std::string size, int auraLevel, int separateParts, std::string vision);
	void deleteTurret(string location);
	void updateTurret(std::string location, std::string size, int auraLevel, int separateParts, std::string vision);
	void saveTurret(std::string location);
	void modeChange(const QString &mode);
	void changeMainPath(string path);
	void changeMyListPath(string path);
	void allCriteriaPopulate(std::vector<Turret> turrets);
};

