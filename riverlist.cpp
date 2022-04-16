#include "riverlist.h"
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QApplication>

RiverList::RiverList(QObject* parent):QAbstractListModel(parent)
{
    add("Волга", "3530", "Каспийское море", "254", "1360");
    add("Сена", "776", "Ла-Манш", "34", "78");
    add("Турнеэльвен", "565", "Ботанический залив", "27", "40");
}

RiverList::~RiverList()
{

}

int RiverList::rowCount(const QModelIndex&) const
{
    return listOfRivers.size();
}


QVariant RiverList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= listOfRivers.size())
            return QVariant();
      {
        switch (role) {
                case name:
                    return QVariant(listOfRivers.at(index.row()).getName());
                case lenght:
                    return QVariant(listOfRivers.at(index.row()).getLenght());
                case flow:
                    return QVariant(listOfRivers.at(index.row()).getFlow());
                case runoff:
                    return QVariant(listOfRivers.at(index.row()).getRunoff());
                case area:
                    return QVariant(listOfRivers.at(index.row()).getArea());

                default:
                    return QVariant();
            }

    }
}

QHash<int, QByteArray> RiverList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[name] = "nameOfRiver";
    roles[lenght] = "lenghtOfRiver";
    roles[flow] = "flowOfRiver";
    roles[runoff] = "runoffOfRiver";
    roles[area] = "areaOfRiver";
       return roles;
}

void RiverList::add(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const QString& areaRiv){
     River river;
     river.setName(nameRiv);
     river.setLenght(lenghtRiv);
     river.setFlow(flowRiv);
     river.setRunoff(runoffRiv);
     river.setArea(areaRiv);

    beginInsertRows(QModelIndex(),listOfRivers.size(),listOfRivers.size());
    listOfRivers.append(river);  //добавление в конец списка
    endInsertRows();

}

QAbstractListModel* RiverList::getModel(){
    return this;
}

void RiverList::del(const int index){

     if (index >= 0 && index < listOfRivers.size())
     {

    // сообщение модели о процессе удаления данных
         beginRemoveRows(QModelIndex(), index, index);
        listOfRivers.removeAt(index);
              endRemoveRows();
     }
     else qDebug() << "Error index";

}

QString RiverList::count(const QString& textSelArea){
    int count = 0;
    for(int i = 0; i < listOfRivers.size(); i++)
        if(listOfRivers[i].getArea().toInt() > textSelArea.toInt())
            count++;
    QString c = QString::number(count);
    return c;
    //QMessageBox messBox;
    //messBox.setWindowTitle("Всё подсчиталось!");
    //messBox.setText("Количество рек, где площадь бассейна превышает " + textSelArea + ", равно " + c + "!");
}

void RiverList::edit(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const QString& areaRiv, const int index) {
     if(index >= 0 && index < listOfRivers.size() )
     {
        auto& currentRiver = listOfRivers[index];
        if (currentRiver.getName().compare(nameRiv)!=0 || currentRiver.getLenght() != lenghtRiv || currentRiver.getFlow() != flowRiv
                || currentRiver.getRunoff() != runoffRiv || currentRiver.getArea() != areaRiv)
        {
            currentRiver.setName(nameRiv);
            currentRiver.setLenght(lenghtRiv);
            currentRiver.setFlow(flowRiv);
            currentRiver.setRunoff(runoffRiv);
            currentRiver.setArea(areaRiv);

            auto modelIndex = createIndex(index, 0);
            emit dataChanged(modelIndex, modelIndex);
            qDebug() << listOfRivers[index].getArea();
        }

     }
      else qDebug() << "Error index";
}
