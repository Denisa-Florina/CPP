#pragma once
#include "Locatar.h"
#include <QAbstractTableModel>
#include <vector>

using std::vector;
class MyListModel :public QAbstractListModel {
    vector<Locatar> all;
public:
    MyListModel(const vector<Locatar>& all) : all{ all } {}


    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return all.size();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        
        if (role == Qt::DisplayRole) {
            qDebug() << index;
            return QString::fromStdString(all[index.row()].get_apartament()+" "+all[index.row()].get_nume_proprietar()+" "+ all[index.row()].get_tip() +" "+ to_string(all[index.row()].get_suprafata()));
        }
        return QVariant{};
    }

    void set(const vector<Locatar>& locatari) {
        all = locatari;
        auto topIndex = createIndex(0, 0);
        auto botIndex = createIndex(rowCount(), 0);
        emit dataChanged(topIndex, botIndex);
        emit layoutChanged();
    }
};
