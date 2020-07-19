#pragma once
#include <qabstractitemmodel.h>
#include "ServiceWatchMan.h"
#include <vector>
#include <string>

using namespace std;

class TurretTableView : public QAbstractTableModel
{
private:
	ServiceWatchMan& serviceWatch;

public:
	TurretTableView(ServiceWatchMan& service, QObject* parent = Q_NULLPTR);
	~TurretTableView();

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

