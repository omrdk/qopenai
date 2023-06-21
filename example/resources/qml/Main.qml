import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

import example 1.0
import QOpenAI 1.0

Window {
  id: appWindow

  property bool isMobilePlatform: Qt.platform.os === "android" || Qt.platform.os === "ios"

  width: isMobilePlatform ? Screen.width : 360
  height: isMobilePlatform ? Screen.height : 640

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
      console.log("Error:", error)
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
      console.log("Error:", error)
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
      console.log("Error:", error)
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
      console.log("Error:", error)
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
      console.log("Error:", error)
    }
  }

  QOpenAIImageEdits {
    id: openAIImageEdits

    endPoint: QOpenAI.ImageEdits

    onRequestFinished: function (jsonObject) {
      let imageUrls = jsonObject.data
      for (var i = 0; i < imageUrls.length; i++) {
        let url = imageUrls[i].url
        openAIImageEdits.messageModel.insertMessage(url, QOpenAIMessage.Role.Assistant)
      }
    }

    onRequestError: function (error) {
      console.log("Error:", error)
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
      console.log("Error:", error)
    }
  }
}
