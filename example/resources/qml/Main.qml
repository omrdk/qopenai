import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

import example
import QOpenAI

Window {
  id: appWindow

  property bool isMobilePlatform: Qt.platform.os === "android" || Qt.platform.os === "ios"

  width: isMobilePlatform ? Screen.width * Screen.pixelDensity : 360
  height: isMobilePlatform ? Screen.height * Screen.pixelDensity : 640

  minimumHeight: isMobilePlatform ? Screen.width : 640
  maximumHeight: minimumHeight
  minimumWidth: isMobilePlatform ? Screen.width : 360
  maximumWidth: minimumWidth

  visible: true
  title: qsTr("My AI")

  ChatPage {
    id: chatPage

    anchors {
      fill: parent
      bottomMargin: Qt.inputMethod.visible ? Qt.inputMethod.keyboardRectangle.height - chatPage.inputItem.height : 0
    }
  }

  QOpenAICompletions {
    id: openAICompletions

    endPoint: QOpenAI.Completions
    model: "text-davinci-003"

    onRequestFinished: function (jsonObject) {
      const content = jsonObject.choices[0].text
      openAICompletions.messageModel.insertMessage(content, QOpenAIMessage.Role.Assistant)
    }

    onRequestError: function (error) {
      console.log("Error message:", error)
    }
  }

  QOpenAIChat {
    id: openAIChatCompletions

    endPoint: QOpenAI.ChatCompletions
    model: "gpt-3.5-turbo"
    systemMessage: chatPage.instructionItem.text

    onRequestFinished: function (jsonObject) {
      const content = jsonObject.choices[0].message.content
      openAIChatCompletions.messageModel.insertMessage(content, QOpenAIMessage.Role.Assistant)
    }

    onRequestError: function (error) {
      console.log("Error message:", error)
    }
  }

  QOpenAIEdits {
    id: openAIEdits

    endPoint: QOpenAI.Edits
    model: "text-davinci-edit-001" // code-davinci-edit-001
    instruction: chatPage.instructionItem.text

    onRequestFinished: function (jsonObject) {
      const content = jsonObject.choices[0].text
      openAIEdits.messageModel.insertMessage(content, QOpenAIMessage.Role.Assistant)
    }

    onRequestError: function (error) {
      console.log("Error message:", error)
    }
  }

  QOpenAIAudio {
    id: openAIAudio

    endPoint: {
      switch (chatPage.endpointsItem.currentEndpoint) {
      case QOpenAI.Transcriptions:
        return QOpenAI.Transcriptions
      case QOpenAI.Translations:
        return QOpenAI.Translations
      default:
        return QOpenAI.Transcriptions
      }
    }

    model: "whisper-1"

    onRequestFinished: function (jsonObject) {
      const content = jsonObject.text
      openAIAudio.messageModel.insertMessage(content, QOpenAIMessage.Role.Assistant)
    }

    onRequestError: function (error) {
      console.log("Error message:", error)
    }
  }

  QOpenAIImage {
    id: openAIImage

    endPoint: QOpenAI.ImageGenerations

    onRequestFinished: function (jsonObject) {
      let imageUrls = jsonObject.data
      for (var i = 0; i < imageUrls.length; i++) {
        let url = imageUrls[i].url
        openAIImage.messageModel.insertMessage(url, QOpenAIMessage.Role.Assistant)
      }
    }

    onRequestError: function (error) {
      console.log("Error message:", error)
    }
  }

  QOpenAIImageEdits {
    id: openAIImageEdits

    endPoint: QOpenAI.ImageEdits
    prompt: chatPage.inputItem.textAreaItem.text // take care of this

    onRequestFinished: function (jsonObject) {
      let imageUrls = jsonObject.data
      for (var i = 0; i < imageUrls.length; i++) {
        let url = imageUrls[i].url
        openAIImageEdits.messageModel.insertMessage(url, QOpenAIMessage.Role.Assistant)
      }
    }

    onRequestError: function (error) {
      console.log("Error message:", error)
    }
  }

  QOpenAIImageVariations {
    id: openAIImageVariations

    endPoint: QOpenAI.ImageVariations

    onRequestFinished: function (jsonObject) {
      let imageUrls = jsonObject.data
      for (var i = 0; i < imageUrls.length; i++) {
        let url = imageUrls[i].url
        openAIImageVariations.messageModel.insertMessage(url, QOpenAIMessage.Role.Assistant)
      }
    }

    onRequestError: function (error) {
      console.log("Error message:", error)
    }
  }
}
