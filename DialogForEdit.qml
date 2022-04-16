import QtQuick 6.0
import QtQuick.Window 6.0
import QtQuick.Controls 6.0 // это версия библиотеки, содержащей Contol (аналоги виджетов) для версии Qt 5.6
import QtQuick.Layouts 6.0


Window {
    id: root
    modality: Qt.ApplicationModal  // окно объявляется модальным
    title: qsTr("Редактирование информации о реке")
    minimumWidth: 400
    maximumWidth: 400
    minimumHeight: 200
    maximumHeight: 200

    property int currentIndex: -1

    GridLayout {
        anchors { left: parent.left; top: parent.top; right: parent.right; bottom: buttonCancel.top; margins: 10 }
        columns: 2

        Label {
            Layout.alignment: Qt.AlignRight  // выравнивание по правой стороне
            text: qsTr("Название реки:")
        }
        TextField {
            id: textName
            Layout.fillWidth: true
            placeholderText: qsTr("Введите название")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Протяженность:")
        }
        TextField {
            id: textLenght
            Layout.fillWidth: true
            placeholderText: qsTr("Введите длину")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Куда впадает?")
        }
        TextField {
            id: textFlow
            Layout.fillWidth: true
            placeholderText: qsTr("Введите, куда впадает река")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Годовой сток:")
        }
        TextField {
            id: textRunoff
            Layout.fillWidth: true
            placeholderText: qsTr("Введите годовой сток")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Площадь бассейна:")
        }
        TextField {
            id: textArea
            Layout.fillWidth: true
            placeholderText: qsTr("Введите площадь бассейна")
        }
    }
    Button {
        visible: {textName.length>0 && textLenght.length>0 && root.currentIndex <0}
        anchors { right: buttonCancel.left; verticalCenter: buttonCancel.verticalCenter; rightMargin: 10 }
        text: qsTr("Добавить в список")
        width: 100
        onClicked: {
            root.hide()
            add(textName.text, textLenght.text, textFlow.text, textRunoff.text, textArea.text)
        }
    }
    Button {
        visible: {root.currentIndex>=0}
        anchors { right: buttonCancel.left; verticalCenter: buttonCancel.verticalCenter; rightMargin: 10 }
        text: qsTr("Применить")
        width: 100
        onClicked: {
            root.hide()
            edit(textName.text, textLenght.text, textFlow.text, textRunoff.text, textArea.text, root.currentIndex)
        }
    }
    Button {
        id: buttonCancel
        anchors { right: parent.right; bottom: parent.bottom; rightMargin: 10; bottomMargin: 10 }
        text: qsTr("Отменить")
        width: 100
        onClicked: {
             root.hide()
        }
    }


    function execute(name, lenght, flow, runoff, area, index){
        textName.text = name
        textLenght.text = lenght
        textFlow.text = flow
        textRunoff.text = runoff
        textArea.text = area
        root.currentIndex = index

        root.show()
    }
 }
