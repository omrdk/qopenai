import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

import example 1.0

import QOpenAI 1.0

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
    prompt: ""
    suffix: ""
    maxTokens: 16
    temperature: 1.0
    topP: 1.0
    n: 1
    stream: false
    logProbs: 0
    echo: false
    stop: ""
    presencePenalty: 0.0
    frequencyPenalty: 0.0
    bestOf: 1
    logitBias: []
    user: ""

    onRequestFinished: function (content) {
      openAICompletions.messageModel.insertMessage(content, QOpenAIMessage.Role.ASSISTANT)
    }

    onRequestError: function (error) {
      console.log("REQUEST ERROR:", error)
    }
  }

  QOpenAIChat {
    id: openAIChatCompletions

    endPoint: QOpenAI.ChatCompletions
    model: "gpt-3.5-turbo"
    temperature: 1.0
    topP: 1.0
    n: 1
    stream: false
    stop: ""
    maxTokens: 2048
    presencePenalty: 0.0
    frequencyPenalty: 0.0
    logitBias: []
    user: ""

    onRequestFinished: function (content) {
      openAIChatCompletions.messageModel.insertMessage(content, QOpenAIMessage.Role.ASSISTANT)
    }

    onRequestError: function (error) {
      console.log("REQUEST ERROR:", error)
    }
  }

  QOpenAIEdits {
    id: openAIEdits

    endPoint: QOpenAI.Edits
    model: "text-davinci-edit-001" // code-davinci-edit-001
    input: ""
    instruction: chatPage.instructionItem.text
    n: 1
    temperature: 1.0
    topP: 1.0

    onRequestFinished: function (content) {
      openAIEdits.messageModel.insertMessage(content, QOpenAIMessage.Role.ASSISTANT)
    }

    onRequestError: function (error) {
      console.log("REQUEST ERROR:", error)
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
    responseFormat: "json"
    temperature: 1.0

    onRequestFinished: function (content) {
      openAIAudio.messageModel.insertMessage(content, QOpenAIMessage.Role.ASSISTANT)
    }

    onRequestError: function (error) {
      console.log("REQUEST ERROR:", error)
    }
  }

  QOpenAIImage {
    id: openAIImage

    endPoint: QOpenAI.ImageGenerations
    prompt: "" // NOOP
    n: 1
    imageSize: "512x512"
    responseFormat: "url"
    user: ""

    onRequestFinished: function (content) {
      openAIImage.messageModel.insertMessage(content, QOpenAIMessage.Role.ASSISTANT)
    }

    onRequestError: function (error) {
      console.log("REQUEST ERROR:", error)
    }
  }

  QOpenAIImageEdits {
    id: openAIImageEdits

    endPoint: QOpenAI.ImageEdits
    image: "" // NOOP
    mask: "" // NOOP
    prompt: chatPage.inputItem.textAreaItem.text
    n: 1
    imageSize: "512x512"
    responseFormat: "url"
    user: ""

    onRequestFinished: function (content) {
      openAIImageEdits.messageModel.insertMessage(content, QOpenAIMessage.Role.ASSISTANT)
    }

    onRequestError: function (error) {
      console.log("REQUEST ERROR:", error)
    }
  }

  QOpenAIImageVariations {
    id: openAIImageVariations

    endPoint: QOpenAI.ImageVariations
    image: "" // NOOP
    n: 1
    imageSize: "512x512"
    responseFormat: "url"
    user: ""

    onRequestFinished: function (content) {
      openAIImageVariations.messageModel.insertMessage(content, QOpenAIMessage.Role.ASSISTANT)
    }

    onRequestError: function (error) {
      console.log("REQUEST ERROR:", error)
    }
  }
}
