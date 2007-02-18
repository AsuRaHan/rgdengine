#pragma once

namespace input
{

  //������������ ������������ ������
  enum ECommand
  {
    CommandUp,
    CommandDown,
    CommandRotateCW,
    CommandRotateCCW,
    CommandForward,
    CommandBackward,
    CommandStarfeLeft,
    CommandStarfeRight,
    CommandSlide,
    CommandRotateOX,
    CommandRotateOY,
    CommandEscape,
    //... ������ �������

    CommandEnumSize,
    InvalidCommand,
  };

  const std::string& ECommand2String (ECommand);           //��������� ������, ��������������� enum-��������
  ECommand           String2ECommand (const std::string&); //��������� enum-��������, ���������������� ������

}