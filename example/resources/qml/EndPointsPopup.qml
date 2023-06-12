import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import example
import QOpenAI

PopupItem {
  id: root

  component Seperator: Rectangle {
    width: parent.width
    height: 1
    color: "lightgray"
    radius: 18
  }

  property int currentEndpoint: listView.currentIndex

  contentHeight: listView.contentHeight

  ListView {
    id: listView

    anchors.fill: parent

    model: ["Completions", "Chat Completions", "Edits", "Image Creations", "Image Edits", "Image Variations", "Embeddings", "Transcriptions", "Translations", "Moderations"]

    interactive: false
    currentIndex: 1

    delegate: Rectangle {
      id: delegate

      width: parent.width
      height: 36

      color: listView.currentIndex === index ? "lightgray" : marea.pressed ? "lightgray" : "white"

      Seperator {
        anchors.top: parent.top
        visible: index
      }

      RowLayout {
        width: parent.width
        spacing: 10

        IconItem {
          id: icon

          Layout.preferredHeight: 36
          Layout.preferredWidth: 36

          imageItem.source: {
            switch (index) {
            case QOpenAI.Completions:
            case QOpenAI.ChatCompletions:
            case QOpenAI.Edits:
              return "qrc:/TEXT"
            case QOpenAI.Transcriptions:
            case QOpenAI.Translations:
              return "qrc:/MICROPHONE"
            case QOpenAI.ImageGenerations:
            case QOpenAI.ImageEdits:
            case QOpenAI.ImageVariations:
              return "qrc:/IMAGE"
            }
          }
        }

        Text {
          id: text

          Layout.fillWidth: true
          Layout.preferredHeight: 36

          verticalAlignment: Text.AlignVCenter
          text: modelData

          font.italic: !marea.enabled

          MouseArea {
            id: marea

            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
              listView.currentIndex = index
              root.close()
            }
          }
        }
      }
    }
  }
}
