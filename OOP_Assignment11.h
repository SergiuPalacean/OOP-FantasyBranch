#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OOP_Assignment11.h"
#include "Service.h"
#include "ServiceWatchMan.h"


class OOP_Assignment11 : public QMainWindow
{
	Q_OBJECT

public:
	OOP_Assignment11(Service& serv, ServiceWatchMan& servWatch, QWidget *parent = Q_NULLPTR);

private:
	Ui::OOP_Assignment11Class ui;
	Service& service;
	ServiceWatchMan& serviceWatch;
	void showMessageBox(QString message);
	void emptyLines();
	void updateMainList();
	void updateMyList(vector<Turret> turrets);

signals:
	

public slots:
	void addTurret();
	void removeTurret();
	void updateTurret();
	void saveTurret();
	void changeMainPath();
	void changeMyListPath();
	void nextTurret();
	void changeMode(const QString& mode);
	void undo();
	void redo();
	void openWindow();
	void openMyList();
	void filterCriteria();
};
