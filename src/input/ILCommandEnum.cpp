#include "precompiled.h"

#include "input/ILCommandEnum.h"

namespace input
{

  //��������� ����� ��� �������� ������������� ������������ ����������
  //����� ������, ������� ����� ��� ����, ����� � ��� ����������� ���������
  //std::map<ECommand, std::string>
  class LocalClassCommandEnum2String
  {
    typedef std::map<ECommand, std::string> Enum2String;
    Enum2String enum2string;

  public:
    //����������, � ������� ��� ������� enum-�������� �������� ��������������� ��� ������
    LocalClassCommandEnum2String ()
    {
      enum2string[CommandUp]          = "CommandUp";
      enum2string[CommandDown]        = "CommandDown";
      enum2string[CommandRotateCW]    = "CommandRotateCW";
      enum2string[CommandRotateCCW]   = "CommandRotateCCW";
      enum2string[CommandForward]     = "CommandForward";
      enum2string[CommandBackward]    = "CommandBackward";
      enum2string[CommandStarfeLeft]  = "CommandStarfeLeft";
      enum2string[CommandStarfeRight] = "CommandStarfeRight";
      enum2string[CommandSlide]       = "CommandSlide";
      enum2string[CommandRotateOX]    = "CommandRotateOX";
      enum2string[CommandRotateOY]    = "CommandRotateOY";
      enum2string[CommandEscape]      = "CommandEscape";
      //... ������ �������
    }

    //��������� ������, ��������������� enum-��������
    const std::string& ECommand2String (ECommand eCommand)
    {
      Enum2String::const_iterator i = enum2string.find(eCommand);
      if (i != enum2string.end())
        return i->second;

      //... ��������, ��� ��� ������ enum-�������� ������ �� �������
      static std::string empty = "";
      return empty;
    }

    //��������� enum-��������, ���������������� ������
    ECommand String2ECommand (const std::string &str)
    {
      Enum2String::const_iterator i   = enum2string.begin(),
                                  end = enum2string.end();
      while (i != end)
      {
        if (i->second == str)
          return i->first;
        ++i;
      }

      //... ��������, ��� ��� ����� ������ ��� ���������������� ��� enum-��������
      return InvalidCommand;
    }
  };

  //������������ ��������� ������ LocalClassCommandEnum2String
  //(������������ ������ � ���� �����)
  LocalClassCommandEnum2String ce2s; //'C'ommand'E'num to 'S'tring

  //��������� ������, ��������������� enum-��������
  const std::string& ECommand2String (ECommand eCommand)
  {
    return ce2s.ECommand2String(eCommand);
  }

  //��������� enum-��������, ���������������� ������
  ECommand String2ECommand (const std::string &str)
  {
    return ce2s.String2ECommand(str);
  }

} //namespace input