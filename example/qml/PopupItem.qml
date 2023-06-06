import QtQuick
import QtQuick.Controls

Popup {
  id: root

  padding: 5
  closePolicy: Popup.NoAutoClose

  background: Rectangle {
    color: "white"
    border {
      color: "gray"
      width: 1
    }
    radius: 10
  }
}
