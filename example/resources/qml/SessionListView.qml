import QtQuick
import QtQuick.Controls

import QOpenAI

ListView {
  id: root

  spacing: 5
  clip: true

  delegate: TextArea {
    id: delegateText

    required property string content
    required property int role

    x: role === QOpenAIMessage.Role.Assistant ? 0 : parent.width - width

    width: (implicitWidth >= parent.width * 2 / 3 ? parent.width * 2 / 3 : implicitWidth) + 10
    height: implicitHeight + 10

    background: Rectangle {
      color: "transparent"
      radius: 10
      border {
        width: 1
        color: "gray"
      }
    }

    color: "black"

    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignVCenter

    textFormat: TextArea.RichText

    readOnly: true

    text: isValidURL(content) ? ("<a href='" + content + "'>" + "generated_image" + "</a>") : content

    onLinkActivated: Qt.openUrlExternally(link)

    wrapMode: implicitWidth >= parent.width * 2 / 3 ? TextArea.WordWrap : TextArea.NoWrap

    function isValidURL(str) {
      var regexp = /(ftp|http|https):\/\/(\w+:{0,1}\w*@)?(\S+)(:[0-9]+)?(\/|\/([\w#!:.?+=&%@!\-\/]))?/
      return regexp.test(str)
    }
  }

  add: Transition {
    NumberAnimation {
      property: "opacity"
      from: 0
      to: 1.0
      duration: 400
    }
    NumberAnimation {
      property: "scale"
      from: 0
      to: 1.0
      duration: 400
    }
  }

  onCountChanged: {
    Qt.callLater(root.positionViewAtEnd)
  }
}
