#include "precompiled.h"

#include "input/ILSchemeImplSimple.h"

#include "input/ILScheme.h"
#include "input/ILCommandEnum.h"

namespace input
{

  //�������� ������ �������-�������
  void CSchemeImplSimple::load (std::istream &instr)
  {
    using namespace std;

    //������:
    // command name: (device name, control name) ...
    // ';' - ���������� �� ����� ������

    const int bufsize = 1024;
    char      buf[bufsize]; //�����, � ������� �������� ������
    char     *str,          //��������������� ��������� ��� ������� ������
             *rstr;

    string                       command;
    string                       device;
    string                       control;
    vector<pair<string,string> > pairs;

    while (instr)
    {
      command.clear();
      device.clear();
      control.clear();
      pairs.clear();

      //��������� ������ �� ������
      instr.getline(buf,bufsize);

      //������� ��������� �� ������ ������������ ������
      str = buf;
      str += strspn(&(str[0])," \t");

      //������������� ������ ������ � ������ � ������������
      if (str[0]==0 || str[0]==';')
        continue;

      //������� ��� �������
      rstr = strchr(str,':');
      if (!rstr)
        continue;
      rstr[0]=0;
      ++rstr;
      command = str;
      str = rstr;

      //������� ����� ���������
      while (1)
      {
        str += strspn(&(str[0])," \t");
        if (str[0]==0 || str[0]==';')
          break;

        //�������� ����������
        str = strchr(str,'(');
        if (!str)
          break;
        ++str;
        str += strspn(&(str[0])," \t");
        if (str[0]==0 || str[0]==';')
          break;
        rstr = strchr(str,',');
        if (!rstr)
          break;
        rstr[0]=0;
        ++rstr;
        device = str;
        str = rstr;

        //�������� ��������
        str += strspn(&(str[0])," \t");
        if (str[0]==0 || str[0]==';')
          break;
        rstr = strchr(str,')');
        if (!rstr)
          break;
        rstr[0]=0;
        ++rstr;
        control = str;
        str = rstr;

        //��������� ���� <��� ����������, ��� ��������>
        pairs.push_back(make_pair<string,string>(device,control));
      }

      //������ ������� c ����������
      if (pairs.size() > 0)
      {
        ECommand cmd;
        EDevice  dev;
        EControl ctrl;

        cmd = String2ECommand(command);
        if (cmd == InvalidCommand)
          break; //... � ����� �� ������ ��������� ��� �������, �������� �� ������������ �� ���� �������� �� enum

        vector<pair<string,string> >::const_iterator i   = pairs.begin(),
                                                     end = pairs.end();
        while (i != end)
        {
          dev  = String2EDevice  (i->first);
          ctrl = String2EControl (i->second);
          if (dev == InvalidDevice)
            continue; //... � ����� �� ������ ��������� ��� ����������, �������� �� ����������� enum
          if (ctrl == InvalidControl)
            continue; //... � ����� �� ������ ��������� ��� ����������, �������� �� ����������� enum
          
          CScheme::AddCommandBinding(cmd,dev,ctrl);
          ++i;
        }
      } //if (pairs.size() > 0)
    } //while (instr)
  }

  //���������� ������ �������-�������
  void CSchemeImplSimple::save (std::ostream &outstr)
  {
    using namespace std;

    for (int c=0; c<CommandEnumSize; ++c)
    {
      outstr << ECommand2String((ECommand)c) << ": ";

      CScheme::iterator i   = CScheme::GetCommandBinding((ECommand)c).first,
                        end = CScheme::GetCommandBinding((ECommand)c).second;
      while (i != end)
      {
        outstr << "(";
        outstr << EDevice2String (i->second.first)  << ", ";
        outstr << EControl2String(i->second.second) << ") ";
        ++i;
      }

      outstr << endl;
    }
  }

} //namespace input
