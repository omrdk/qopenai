import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import example 1.0
import QOpenAI 1.0

Row {
  id: root

  property alias switchButtonItem: switchButton
  property alias textAreaItem: textArea
  property bool audioRecording: false

  signal messageSent(string message)
  signal loadImageRequested

  // workaround for iOS keyboard shifting, basically changes the bottom margin of chatPage when it is visible
  EventInstaller {
    id: eventInstaller
  }

  Rectangle {
    id: containerItem

    width: parent.width
    height: childrenRect.height

    anchors {
      margins: 5
      verticalCenter: parent.verticalCenter
    }

    border {
      color: "gray"
      width: 1
    }

    radius: 18

    RowLayout {
      id: rowLayout

      width: parent.width

      spacing: 0

      IconButton {
        id: switchButton

        Layout.preferredHeight: 36
        Layout.preferredWidth: 36
        Layout.alignment: Qt.AlignBottom

        imageItem.source: "qrc:/OPTIONS"

        onClicked: {
          endPoints.opened ? endPoints.close() : endPoints.open()
        }
      }

      TextAreaItem {
        id: textArea

        Layout.fillWidth: true

        enabled: {
          switch (endPoints.currentEndpoint) {
          case QOpenAI.Completions:
          case QOpenAI.ChatCompletions:
          case QOpenAI.Edits:
          case QOpenAI.ImageGenerations:
            return true
          default:
            return false
          }
        }

        placeHolderItem.text: "Enter your message here"

        Keys.onReturnPressed: sendButton.clicked()

        Component.onCompleted: {
          eventInstaller.setupEventFilter(textArea)
        }
      }

      IconButton {
        id: sendButton

        Layout.preferredHeight: 36
        Layout.preferredWidth: 36
        Layout.alignment: Qt.AlignBottom

        imageItem.source: {
          switch (endPoints.currentEndpoint) {
          case QOpenAI.Transcriptions:
          case QOpenAI.Translations:
            return "qrc:/MICROPHONE"
          case QOpenAI.ImageVariations:
          case QOpenAI.ImageEdits:
            return "qrc:/IMAGE"
          default:
            return "qrc:/SEND"
          }
        }

        colorOverlay: root.audioRecording ? "red" : "black"

        onClicked: {
          switch (endPoints.currentEndpoint) {
          case QOpenAI.Completions:
          case QOpenAI.ChatCompletions:
          case QOpenAI.Edits:
          case QOpenAI.ImageGenerations:
            if (textArea.length) {
              root.messageSent(textArea.text)
              textArea.clear()
            }
            break
          case QOpenAI.ImageEdits:
          case QOpenAI.ImageVariations:
            root.loadImageRequested()
            break
          case QOpenAI.Transcriptions:
          case QOpenAI.Translations:
            openAIAudio.audioRecorder.toggleRecord()
            break
          }
        }
      }
    }
  }
}
