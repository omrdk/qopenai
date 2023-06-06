import QtQuick
import Qt5Compat.GraphicalEffects

IconItem {
  id: root

  property bool mouseEventsEnabled: false
  property bool containsMouse: marea.containsMouse

  signal clicked

  color: mouseEventsEnabled && marea.pressed ? "lightgray" : "transparent"

  MouseArea {
    id: marea

    anchors.fill: parent
    hoverEnabled: true

    onClicked: {
      root.clicked()
    }
  }
}
