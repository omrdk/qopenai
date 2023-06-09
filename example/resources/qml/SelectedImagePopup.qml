import QtQuick
import QtQuick.Layouts

import example 1.0
import QOpenAI 1.0

PopupItem {
  id: root

  property alias imageItem: interactiveImage
  property bool alphaChannelCanBeModified: false

  signal acceptClicked
  signal cancelClicked

  ColumnLayout {
    id: columnLayout

    anchors.fill: parent

    InteractiveImage {
      id: interactiveImage

      Layout.fillWidth: true
      Layout.fillHeight: true

      enabled: root.alphaChannelCanBeModified
    }

    RowLayout {
      id: row

      Layout.fillWidth: true
      Layout.preferredHeight: 36
      Layout.maximumHeight: 36

      spacing: 5

      IconButton {
        id: cancelButton

        Layout.fillHeight: true
        Layout.fillWidth: true

        imageItem.source: "qrc:/CANCEL"
        mouseEventsEnabled: true

        onClicked: {
          root.cancelClicked()
        }
      }

      IconButton {
        id: acceptButton

        Layout.fillHeight: true
        Layout.fillWidth: true

        imageItem.source: "qrc:/SEND"
        mouseEventsEnabled: true

        onClicked: {
          root.acceptClicked()
        }
      }
    }
  }
}
