#pragma once
#include <qmainwindow.h>
#include "ui_secondWindow.h"
#include "ServiceWatchMan.h"
#include "TurretTableView.h"
#include "Observer.h"
#include <qmessagebox.h>

class SecondaryWindow : public QMainWindow, public Observer
{

	Q_OBJECT

public:
	SecondaryWindow(ServiceWatchMan& service, QWidget* parent = Q_NULLPTR);

private:
	Ui::MainWindow ui;
	ServiceWatchMan& serviceWatch;
	TurretTableView* tableModel;
	void update() override;
	void showMessageBox(QString message);

public slots:
	void undo();
	void redo();
};

