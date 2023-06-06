import QtQuick
import QtQuick.Controls

TextArea {
  id: root

  property alias placeHolderItem: placeholder

  background: Rectangle {
    color: "transparent"
  }

  activeFocusOnPress: true
  color: "black"
  font.pixelSize: 16
  wrapMode: Text.Wrap

  Text {
    id: placeholder

    anchors.centerIn: parent

    text: ""
    color: "gray"
    visible: root.text.length === 0
  }
}
