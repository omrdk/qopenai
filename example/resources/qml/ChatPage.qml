import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import example
import QOpenAI

Rectangle {
  id: root

  // used only when the platform is iOS
  property var nativeImagePickerObj: null

  property alias inputItem: chatInput
  property alias instructionItem: instruction
  property alias endpointsItem: endPoints

  ColumnLayout {
    id: container

    anchors.fill: parent

    spacing: 0

    TextAreaItem {
      id: instruction

      Layout.fillWidth: true
      Layout.preferredHeight: 48

      background: Rectangle {
        border {
          color: "gray"
          width: selectedImagePopup.visible ? 0 : 1
        }
      }

      placeHolderItem.text: {
        switch (endPoints.currentEndpoint) {
        case QOpenAI.ChatCompletions:
          return "Enter system message"
        case QOpenAI.Edits:
          return "Enter instruction"
        case QOpenAI.ImageEdits:
          return "Enter prompt"
        }
        return ""
      }

      verticalAlignment: TextArea.AlignVCenter
      horizontalAlignment: TextArea.AlignHCenter

      visible: {
        switch (endPoints.currentEndpoint) {
        case QOpenAI.ChatCompletions:
        case QOpenAI.Edits:
          return true
        case QOpenAI.ImageEdits:
          if (selectedImagePopup.visible) {
            return true
          }
          break
        }
        return false
      }
    }

    SessionListView {
      id: chatView

      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.margins: 5
      Layout.bottomMargin: 0

      model: {
        switch (endPoints.currentEndpoint) {
        case QOpenAI.Completions:
          return openAICompletions.messageModel
        case QOpenAI.ChatCompletions:
          return openAIChatCompletions.messageModel
        case QOpenAI.Edits:
          return openAIEdits.messageModel
        case QOpenAI.Transcriptions:
        case QOpenAI.Translations:
          return openAIAudio.messageModel
        case QOpenAI.ImageGenerations:
          return openAIImage.messageModel
        case QOpenAI.ImageEdits:
          return openAIImageEdits.messageModel
        case QOpenAI.ImageVariations:
          return openAIImageVariations.messageModel
        }
      }
    }

    ChatInput {
      id: chatInput

      Layout.fillWidth: true
      Layout.margins: 5

      onMessageSent: function (message) {
        switch (endPoints.currentEndpoint) {
        case QOpenAI.Completions:
          openAICompletions.messageModel.insertMessage(message, QOpenAIMessage.Role.UNDEFINED)
          openAICompletions.sendRequest(message)
          break
        case QOpenAI.ChatCompletions:
          openAIChatCompletions.sendRequest(message)
          openAIChatCompletions.messageModel.insertMessage(message, QOpenAIMessage.Role.USER)
          break
        case QOpenAI.Edits:
          openAIEdits.messageModel.insertMessage(message, QOpenAIMessage.Role.UNDEFINED)
          openAIEdits.sendRequest(message)
          break
        case QOpenAI.Transcriptions:
        case QOpenAI.Translations:
          openAIAudio.sendRequest(message)
          break
        case QOpenAI.ImageGenerations:
          openAIImage.messageModel.insertMessage(message, QOpenAIMessage.Role.UNDEFINED)
          openAIImage.sendRequest(message)
          break
        default:
          break
        }
      }

      onLoadImageRequested: {
        if (Qt.platform.os === "ios") {
          root.nativeImagePickerObj.open()
        } else {
          loadImage.open()
        }
      }
    }
  }

  EndPointsPopup {
    id: endPoints

    y: root.height - chatInput.height - height - 5

    width: parent.width - 10
    margins: 5

    closePolicy: chatInput.switchButtonItem.containsMouse ? Popup.NoAutoClose : Popup.CloseOnPressOutside
  }

  FileDialog {
    id: loadImage

    title: "Select an image"
    nameFilters: ["Image files (*.png)", "All files (*.)"]
    currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]

    onAccepted: {
      selectedImagePopup.source = loadImage.selectedFile.toString().replace("file://", "")
      selectedImagePopup.open()
    }
  }

  SelectedImagePopup {
    id: selectedImagePopup

    y: endPoints.currentEndpoint === QOpenAI.ImageEdits ? instruction.height : 0

    width: parent.width
    height: {
      switch (endPoints.currentEndpoint) {
      case QOpenAI.ImageEdits:
        return parent.height - instruction.height
      default:
        return parent.height
      }
    }

    alphaChannelCanBeModified: endPoints.currentEndpoint === QOpenAI.ImageEdits

    onAcceptClicked: {
      if (endPoints.currentEndpoint === QOpenAI.ImageEdits && instruction.text === "") {
        return
      }
      switch (endPoints.currentEndpoint) {
      case QOpenAI.ImageEdits:
        openAIImageEdits.image = source
        openAIImageEdits.sendRequest(instruction.text)
        break
      case QOpenAI.ImageVariations:
        openAIImageVariations.sendRequest(source)
        break
      }
      chatInput.textAreaItem.clear()
      if (Qt.platform.os === "ios") {
        root.nativeImagePickerObj.selectedImage = ""
      } else {
        source = ""
      }
      close()
    }

    onCancelClicked: {
      if (Qt.platform.os === "ios") {
        root.nativeImagePickerObj.selectedImage = ""
      } else {
        source = ""
      }
    }
  }

  // iOS native dialog item dynamically created to access photos when the platform is iOS
  Component.onCompleted: {
    if (Qt.platform.os === "ios") {
      root.nativeImagePickerObj = Qt.createQmlObject(`
                                                     import ImagePicker 1.0

                                                     ImagePicker {
                                                     id: imagePicker
                                                     }
                                                     `, root, "imagePicker")
    }
  }

  // capture photo path
  Connections {
    id: nativeImagePickerHandler
    target: root.nativeImagePickerObj
    enabled: root.nativeImagePickerObj !== null

    function onSelectedImageChanged(selectedImage) {
      selectedImagePopup.source = selectedImage
      console.log("Selected image:", selectedImage)
      selectedImagePopup.open()
    }
  }
}
