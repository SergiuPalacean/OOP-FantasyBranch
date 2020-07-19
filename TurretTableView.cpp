#include "TurretTableView.h"
#include "Turret.h"
#include <QFont>


TurretTableView::TurretTableView(ServiceWatchMan& service, QObject* parent) : QAbstractTableModel{parent}, serviceWatch{service}
{

}

TurretTableView::~TurretTableView()
{

}

int TurretTableView::rowCount(const QModelIndex& parent) const
{
	return this->serviceWatch.get_all_activated_turrets().size();
}

int TurretTableView::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant TurretTableView::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	vector<Turret> turrets = this->serviceWatch.get_all_activated_turrets();
	
	if(row==turrets.size())
		return QVariant();

	Turret turret = turrets[row];

	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(turret.get_location());
		case 1:
			return QString::fromStdString(turret.get_size());
		case 2:
			return QString::fromStdString(to_string(turret.get_auraLevel()));
		case 3:
			return QString::fromStdString(to_string(turret.get_separateParts()));
		case 4:
			return QString::fromStdString(turret.get_vision());
		default:
			break;
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Arial", 12);
		font.setItalic(false);
		return font;
	}
	return QVariant();
}

QVariant TurretTableView::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Location" };
			case 1:
				return QString{ "Size" };
			case 2:
				return QString{ "Aura Level" };
			case 3:
				return QString("Separate Parts");
			case 4:
				return QString("Vision");
			default:
				break;
			}
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Arial", 12);
		font.setBold(true);
		font.setItalic(false);
		return font;
	}
	return QVariant();
}

	
