import QtQuick
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Rectangle {
  id: root

  property color colorOverlay: "black"
  property alias imageItem: image

  Image {
    id: image

    anchors.centerIn: parent

    width: 36
    height: width

    source: root.iconSource
    visible: false
  }

  ColorOverlay {
    id: colorOverlay

    anchors.fill: image

    color: root.colorOverlay
    source: image
  }
}
